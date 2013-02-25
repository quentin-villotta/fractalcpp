#include "App.h"

App::App()
{
	surf_display = NULL;
	fractal = NULL;
	running = true;

	// All of the color functions which will be used
	ColorBlackBlue* color_black_blue = new ColorBlackBlue();
	ColorBlackWhite* color_black_white = new ColorBlackWhite();
	ColorBlackWhiteMod* color_black_white_mod = new ColorBlackWhiteMod();
	ColorBlackWhiteSmooth* color_black_white_smooth = new ColorBlackWhiteSmooth();

	// Putting them in the vector (in order to switch between colors)
	color_functions.push_back(color_black_blue);
	color_functions.push_back(color_black_white);
	color_functions.push_back(color_black_white_mod);
	color_functions.push_back(color_black_white_smooth);

	// Index flags initialization
	id_cur_color = 0;
	id_cur_screenshot = 0;		   
}

bool App::Init()
{
	// Variables to store info from conf file
	int _width_display, _height_display, _max_iter;
	double _zoom_scale, _orbit_re, _orbit_im;
	string _path_pictures, _type;
	
	// Reading conf file
	ifstream file ("fractalcpp.conf");
	if(file)
	{
		string ligne;
		
		while(getline(file, ligne))
		{
			// Splitting the line with the "=" symbol
			int pos_point1= ligne.find('=', 0);
			int pos_point2= ligne.find('=', pos_point1+1);
			string name_param = ligne.substr(0, pos_point1);

			// If there is a comment, we don't save it
			string value_param = ligne.substr(pos_point1+1,pos_point2-(pos_point1+1));
			int pos_point3= value_param.find(' ', 0);
			value_param = value_param.substr(0, pos_point3);
			istringstream iss (value_param);

			// Checking if the parameters are found in the file
			if (name_param == "width") { iss >> _width_display; }
			if (name_param == "height") { iss >> _height_display; }
			if (name_param == "zoom_scale") { iss >> _zoom_scale; }
			if (name_param == "type") { iss >> _type; }
			if (name_param == "path_pictures") { iss >> _path_pictures; }
			if (name_param == "max_iter") { iss >> _max_iter; }
			if (name_param == "orbit_re") { iss >> _orbit_re; }
			if (name_param == "orbit_im") { iss >> _orbit_im; }
		}
		file.close();
	}
	// Error reading conf file
	else
		return false;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;
	surf_display = SDL_SetVideoMode(_width_display, _height_display, 32,
									SDL_HWSURFACE | SDL_DOUBLEBUF);				
	if(surf_display == NULL)
		return false;
	
	// Set parameters from the conf file
	width_display = _width_display;
	height_display = _height_display;
	zoom_scale = _zoom_scale;
	last_mouse_click = make_pair(width_display / 2, height_display / 2);
	type = _type;
	path_pictures = _path_pictures;
	

	// Create new instance of a fractal
	if(_type == "mandelbrot")
	{
		// Mandelbrot centered
		complex<double> z_top_left(-2.1, 1.2);
		complex<double> z_bottom_right(0.6, -1.2);
		
		// Add default position to the stack history
		z_top_left_history.push(z_top_left);
		z_bottom_right_history.push(z_bottom_right);
			
		fractal = new FractalMandelbrot(width_display, height_display,_max_iter,
			z_top_left, z_bottom_right, *color_functions[id_cur_color]);
	}
	else
	{
		// Julia centered
		complex<double> z_top_left(-2.0, 2.0);
		complex<double> z_bottom_right(2.0, -2.0);
		
		// Add default position to the stack history
		z_top_left_history.push(z_top_left);
		z_bottom_right_history.push(z_bottom_right);
		
		complex<double> orbit(_orbit_re, _orbit_im);
		fractal = new FractalJulia(width_display, height_display, _max_iter, 
			z_top_left, z_bottom_right, orbit, *color_functions[id_cur_color]);
	}
	
	return true;
}

void App::Cleanup()
{
	SDL_FreeSurface(surf_display);
	
	delete fractal;
	
	// Cleaning the memory used by coloration function
	for(size_t i = 0; i < color_functions.size(); i++)
		delete color_functions[i];
	color_functions.clear();
	
	// Free the SDL
	SDL_Quit();
}

void App::Render()
{
	// Update window title
	stringstream title;
	title << "Fractal++ | Type : " << type << " | Resolution : ";
	title << width_display << "x" << height_display << 
	" | Maximum iteration : " << fractal->GetMaxIter();
	SDL_WM_SetCaption(title.str().c_str(), NULL);
	
	// Update display
	SDL_BlitSurface(fractal->GetMatrixColor(), NULL, surf_display, NULL);
	SDL_Flip(surf_display);
}

int App::Execute()
{
	if(Init() == false)
		return -1;

	SDL_Event event;

	// While the application is running
	while(running)
	{
		// Managing the events
		while(SDL_PollEvent(&event))
			Event(&event);
		
		Render();
	}

	// Free the memory
	Cleanup();

	return 0;
}

void App::Event(SDL_Event* event)
{		
    if(event->type == SDL_QUIT)
        running = false;

	if(event->type == SDL_MOUSEBUTTONDOWN)
	{
		if(event->button.button == SDL_BUTTON_LEFT)
			last_mouse_click = make_pair(event->button.x, event->button.y);
	}
	if(event->type == SDL_KEYDOWN)
	{
		// Zoom-in
		if(event->key.keysym.sym == SDLK_UP)
		{
			complex<double> new_center = fractal->GetComplexFromPixel(
				last_mouse_click.first, last_mouse_click.second);
			
			z_top_left_history.push(fractal->_z_top_left());
			z_bottom_right_history.push(fractal->_z_bottom_right());
			
			int max_iter_cur = fractal->GetMaxIter();
			fractal->SetMaxIter((int)(max_iter_cur * (1.0 + zoom_scale)));
			
			fractal->ZoomView(new_center, zoom_scale,
				*color_functions[id_cur_color]);			
		}
		// Zoom-out
		else if(event->key.keysym.sym == SDLK_DOWN)
		{
			int max_iter_cur = fractal->GetMaxIter();
			int max_iter_new = (int)(max_iter_cur * (1.0 - zoom_scale));
			fractal->SetMaxIter(max_iter_new <= fractal->GetMaxIterDefault() ?
								fractal->GetMaxIterDefault() : max_iter_new);
			
			fractal->ChangeView(z_top_left_history.top(),
				 				z_bottom_right_history.top(),
								*color_functions[id_cur_color]);
			
			if(z_top_left_history.size() > 1)
				z_top_left_history.pop();
			if(z_bottom_right_history.size() > 1)
				z_bottom_right_history.pop();			
		}
		// Center
		else if(event->key.keysym.sym == SDLK_c)
		{
			complex<double> new_center = fractal->GetComplexFromPixel(
				last_mouse_click.first, last_mouse_click.second);
			fractal->ZoomView(new_center, 0.0, *color_functions[id_cur_color]);
		}
		// Next color
		else if(event->key.keysym.sym == SDLK_n)
		{
			id_cur_color++;
			id_cur_color = (id_cur_color + color_functions.size()) % color_functions.size();
			fractal->UpdateColor(*color_functions[id_cur_color]);
		}
		// Previous color
		else if(event->key.keysym.sym == SDLK_p)
		{
			id_cur_color--;
			id_cur_color = (id_cur_color + color_functions.size()) % color_functions.size();

			fractal->UpdateColor(*color_functions[id_cur_color]);
		}
		// Save image as file
		else if(event->key.keysym.sym == SDLK_s)
		{
			stringstream path_to_file;
			path_to_file << path_pictures << "screenshot_" 
						 << id_cur_screenshot << ".bmp";
			SDL_SaveBMP(surf_display, path_to_file.str().c_str());
			id_cur_screenshot++;
		}
	}
}

int main(int argc, char* argv[])
{
	// Launching the app to plot Fractals
	App app;
	return app.Execute();
}

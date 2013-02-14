#include "App.h"

App::App()
{
	surf_display = NULL;
	fractal = NULL;
	running = true;

	ColorBlackBlue* color_black_blue = new ColorBlackBlue();
	ColorBlackWhite* color_black_white = new ColorBlackWhite();
	ColorBlackWhiteMod* color_black_white_mod = new ColorBlackWhiteMod();
	ColorBlackWhiteSmooth* color_black_white_smooth = new ColorBlackWhiteSmooth();

	color_functions.push_back(color_black_blue);
	color_functions.push_back(color_black_white);
	color_functions.push_back(color_black_white_mod);
	color_functions.push_back(color_black_white_smooth);

	id_cur_color = 0;
	id_cur_screenshot = 0;		   
}

bool App::Init()
{
	// Variables
    int _width_display, _height_display, _max_iter;
    double _zoom_scale, _orbit_re, _orbit_im;
    string _path_pictures, _type;
	
	// Read conf file
	ifstream file ("fractalcpp.conf");
	if (file) {
		string ligne;
		while (getline(file, ligne)) {
			int posPoint1= ligne.find('=', 0);
			int posPoint2= ligne.find('=', posPoint1+1);
			string nameParam = ligne.substr(0, posPoint1);

			string valParam = ligne.substr(posPoint1+1,posPoint2-(posPoint1+1));
			int posPoint3= valParam.find(' ', 0);
			valParam = valParam.substr(0, posPoint3);
			istringstream iss (valParam);

			if (nameParam == "width") { iss >> _width_display; }
			if (nameParam == "height") { iss >> _height_display; }
			if (nameParam == "zoom_scale") { iss >> _zoom_scale; }
			if (nameParam == "type") { iss >> _type; }
			if (nameParam == "path_pictures") { iss >> _path_pictures; }
			if (nameParam == "max_iter") { iss >> _max_iter; }
			if (nameParam == "orbit_re") { iss >> _orbit_re; }
			if (nameParam == "orbit_im") { iss >> _orbit_im; }
		}
		file.close();
	}
	else { return false; }

	// Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;
	surf_display = SDL_SetVideoMode(_width_display, _height_display, 32,
		 SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(surf_display == NULL)
		return false;
	
	// Set the window title
	stringstream title;
	title << "Fractal++ | Type : " << _type << " | Resolution : ";
	title << _width_display << "x" << _height_display << " | Maximum iteration : " << _max_iter;
	SDL_WM_SetCaption(title.str().c_str(), NULL);
	
	// Create new instance of a fractal
	width_display = _width_display;
	height_display = _height_display;
	zoom_scale = _zoom_scale;
	last_mouse_click = make_pair(width_display / 2, height_display / 2);
	
	path_pictures = _path_pictures;

	if(_type == "mandelbrot")
	{
		//Mandelbrot centered
		complex<double> z_top_left(-2.1, 1.2);
		complex<double> z_bottom_right(0.6, -1.2);
		
		z_top_left_history.push(z_top_left);
		z_bottom_right_history.push(z_bottom_right);
			
		fractal = new FractalMandelbrot(width_display, height_display,
			 _max_iter, z_top_left, z_bottom_right, *color_functions[id_cur_color]);
	}
	else
	{
		// Julia centered
		complex<double> z_top_left(-2.0, 2.0);
		complex<double> z_bottom_right(2.0, -2.0);
		
		z_top_left_history.push(z_top_left);
		z_bottom_right_history.push(z_bottom_right);
		
		complex<double> orbit(_orbit_re, _orbit_im);
		fractal = new FractalJulia(width_display, height_display, _max_iter, z_top_left, z_bottom_right, orbit, *color_functions[id_cur_color]);
	}
	
    return true;
}

void App::Cleanup()
{
    SDL_FreeSurface(surf_display);
	
	delete fractal;
	
	for(size_t i = 0; i < color_functions.size(); i++)
		delete color_functions[i];
	color_functions.clear();
	
    SDL_Quit();
}

void App::Render()
{
	SDL_BlitSurface(fractal->GetMatrixColor(), NULL, surf_display, NULL);
	SDL_Flip(surf_display);
}

int App::Execute()
{
    if(Init() == false)
		return -1;

    SDL_Event event;

    while(running)
	{
        
		while(SDL_PollEvent(&event))
            Event(&event);
		
        Render();
    }

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
		//Zoom-in
		if(event->key.keysym.sym == SDLK_UP)
		{
			complex<double> new_center = fractal->GetComplexFromPixel(
				last_mouse_click.first, last_mouse_click.second);
			
			z_top_left_history.push(fractal->_z_top_left());
			z_bottom_right_history.push(fractal->_z_bottom_right());
			
			fractal->ZoomView(new_center, zoom_scale,
				*color_functions[id_cur_color]);			
		}
		//Zoom-out
		else if(event->key.keysym.sym == SDLK_DOWN)
		{
			fractal->ChangeView(z_top_left_history.top(),
				 				z_bottom_right_history.top(),
								*color_functions[id_cur_color]);
			
			if(z_top_left_history.size() > 1)
				z_top_left_history.pop();
			if(z_bottom_right_history.size() > 1)
				z_bottom_right_history.pop();			
		}
		//Center
		else if(event->key.keysym.sym == SDLK_c)
		{
			complex<double> new_center = fractal->GetComplexFromPixel(
				last_mouse_click.first, last_mouse_click.second);
			fractal->ZoomView(new_center, 0.0, *color_functions[id_cur_color]);
		}
		//Next color
		else if(event->key.keysym.sym == SDLK_n)
		{
			id_cur_color++;
			id_cur_color = (id_cur_color + color_functions.size()) % color_functions.size();
			fractal->UpdateColor(*color_functions[id_cur_color]);
		}
		//Previous color
		else if(event->key.keysym.sym == SDLK_p)
		{
			id_cur_color--;
			id_cur_color = (id_cur_color + color_functions.size()) % color_functions.size();

			fractal->UpdateColor(*color_functions[id_cur_color]);
		}
		//Save image as file
		else if(event->key.keysym.sym == SDLK_s)
		{
			stringstream path_to_file;
			path_to_file << path_pictures << "screenshot_" 
						 << id_cur_screenshot << ".bmp";
			SDL_SaveBMP(surf_display, path_to_file.str().c_str());
			id_cur_screenshot++;
		}
	}
	//See http://www.sdltutorials.com/sdl-events for more complex examples
}

int main(int argc, char* argv[])
{
	// Launching the app to plot Fractals
	App app;
    return app.Execute();
}

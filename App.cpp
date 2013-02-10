#include "App.h"

App::App()
{
	surf_display = NULL;
	fractal = NULL;
	running = true;

	//TODO: ne faut-il pas delete ces pointeurs?
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
	//Read conf file
	namespace po = boost::program_options;
    int _width_display, _height_display, _max_iter;
    double _zoom_scale, _orbit_re, _orbit_im;
    string _path_pictures, _type;
	
	po::options_description desc("Options");
	desc.add_options()
		("width", po::value<int>(&_width_display), "Screen width")
		("height", po::value<int>(&_height_display), "Screen height")
		("zoom_scale", po::value<double>(&_zoom_scale), "Zooming ratio")
		("path_pictures", po::value<string>(&_path_pictures), 
			"Directory to save pictures")
		("type", po::value<string>(&_type), "Type of the fractal")
		("max_iter", po::value<int>(&_max_iter), "Maximum number of iteration")
		("orbit_re", po::value<double>(&_orbit_re), "Real part of orbit")
		("orbit_im", po::value<double>(&_orbit_im), "Imag part of orbit");
	
    po::variables_map vm;
    ifstream settings_file("fractalcpp.conf", ifstream::in);
    po::store(po::parse_config_file(settings_file, desc, true), vm);
    settings_file.close();
    po::notify(vm); 
	
	/* // Pour moi, car toujours pas installé Boost
	int _width_display = 800;
	int _height_display = 711;
	double _zoom_scale = 0.20;
	string _type = "julia";
	int _max_iter = 50;
	double _orbit_re = 0.285;
	double _orbit_im = 0.01;
	string _path_pictures = "./pictures/";
	*/

	// Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;
	surf_display = SDL_SetVideoMode(_width_display, _height_display, 32,
		 SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(surf_display == NULL)
		return false;
		
	//Create new instance of a fractal
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
		fractal = new FractalMandelbrot(width_display, height_display,
			 _max_iter, z_top_left, z_bottom_right, *color_functions[id_cur_color]);
	}
	else
	{
		// Julia centered
		complex<double> z_top_left(-2.0, 2.0);
		complex<double> z_bottom_right(2.0, -2.0);
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
			
			fractal->SetMaxIter( (int)((1.05)*fractal->GetMaxIter()) );
			fractal->ZoomView(new_center, zoom_scale, *color_functions[id_cur_color]);
			
		}
		//Zoom-out
		else if(event->key.keysym.sym == SDLK_DOWN)
		{
			complex<double> new_center = fractal->GetComplexFromPixel(
				width_display / 2, height_display / 2);
			int new_max_iter = (int)((0.95)*fractal->GetMaxIter());

			fractal->SetMaxIter( new_max_iter <= 50 ? 50 : new_max_iter );
			fractal->ZoomView(new_center, -zoom_scale, *color_functions[id_cur_color]);
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

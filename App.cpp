#include "App.h"

App::App()
{
	surf_display = NULL;
	fractal = NULL;
	running = true;
	color_functions[0] = &color_black_blue;
	color_functions[1] = &color_black_white;
	color_functions[2] = &color_black_white_mod;
	color_functions[3] = &color_black_white_smooth;
	color_functions[4] = &color_time_escape_dark_rgb;	
	id_cur_color = 0;			   
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
	//TODO: handle path_pictures

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
			fractal->ZoomView(new_center, zoom_scale, *color_functions[id_cur_color]);
			fractal->SetMaxIter( (int)((1.05)*fractal->GetMaxIter()) );
		}
		//Zoom-out
		else if(event->key.keysym.sym == SDLK_DOWN)
		{
			complex<double> new_center = fractal->GetComplexFromPixel(
				width_display / 2, height_display / 2);
			fractal->ZoomView(new_center, -zoom_scale, *color_functions[id_cur_color]);
			int new_max_iter = (int)((0.95)*fractal->GetMaxIter());
			fractal->SetMaxIter( new_max_iter <= 50 ? 50 : new_max_iter );
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
			id_cur_color %= 5;
			fractal->ChangeColor(*color_functions[id_cur_color]);
		}
		//Previous color
		else if(event->key.keysym.sym == SDLK_p)
		{
			id_cur_color--;
			id_cur_color = id_cur_color == -1 ? 4 : id_cur_color;
			id_cur_color %= 5; // in C++ (-1) mod 5 equal -1 and not 4			
			fractal->ChangeColor(*color_functions[id_cur_color]);
		}
	}
	//See http://www.sdltutorials.com/sdl-events for more complex examples
}

int main(int argc, char* argv[])
{
	// Julia
	//complex<double> z_top_left(-2.0, 2.0);
	//complex<double> z_bottom_right(2.0, -2.0);
	//orbit = complex<double>(0.285, 0.01)
	
	App app;
	
    return app.Execute();
}

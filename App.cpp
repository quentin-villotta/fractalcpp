#include "App.h"

App::App(int width, int height, int max_iter, 
	complex<double> z_top_left, complex<double> z_bottom_right, double _zoom_scale)
{
	surf_display = NULL;
	width_display = width;
	height_display = height;
	
	running = true;
	
	zoom_scale = _zoom_scale;
	
	last_mouse_click = make_pair(width / 2, height / 2);
	
	//TODO: add argument to App:App to specify fractal type (mandelbrot, julia, ...)
	fractal = new FractalMandelbrot(width_display, height_display, max_iter,
		z_top_left, z_bottom_right);	
}

bool App::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;
	
	surf_display = SDL_SetVideoMode(width_display, height_display, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(surf_display == NULL)
		return false;

	//Load other ressources here
	
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
			fractal->ZoomView(new_center, zoom_scale);
			fractal->SetMaxIter( (int)((1.05)*fractal->GetMaxIter()) );
			//DEBUG
			cout << "Zoom-in: " << fractal->GetMaxIter() << endl;
		}
		//Zoom-out
		else if(event->key.keysym.sym == SDLK_DOWN)
		{
			complex<double> new_center = fractal->GetComplexFromPixel(
				width_display / 2, height_display / 2);
			fractal->ZoomView(new_center, -zoom_scale);
			int new_max_iter = (int)((0.95)*fractal->GetMaxIter());
			fractal->SetMaxIter( new_max_iter <= 50 ? 50 : new_max_iter );
			//DEBUG
			cout << "Zoom-out: " << fractal->GetMaxIter() << endl;
		}
		//Center
		else if(event->key.keysym.sym == SDLK_c)
		{
			complex<double> new_center = fractal->GetComplexFromPixel(
				last_mouse_click.first, last_mouse_click.second);
			fractal->ZoomView(new_center, 0.0);
		}
		
	}
	//See http://www.sdltutorials.com/sdl-events for more complex examples
}

int main(int argc, char* argv[])
{
	//TODO: parse conf file
	
	double zoom_scale = 0.20;
	
	//Mandelbrot centered
	complex<double> z_top_left(-2.1, 1.2);
	complex<double> z_bottom_right(0.6, -1.2);
	
	// Julia
	//complex<double> z_top_left(-2.0, 2.0);
	//complex<double> z_bottom_right(2.0, -2.0);
	
	App app(800, 710, 50, z_top_left, z_bottom_right, zoom_scale);
	
    return app.Execute();
}

#include "App.h"

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
			fractal->setMaxIter( (int)((1.05)*fractal->getMaxIter()) );
			//DEBUG
			cout << "Zoom-in: " << fractal->getMaxIter() << endl;
		}
		//Zoom-out
		else if(event->key.keysym.sym == SDLK_DOWN)
		{
			complex<double> new_center = fractal->GetComplexFromPixel(
				width_display / 2, height_display / 2);
			fractal->ZoomView(new_center, -zoom_scale);
			int new_max_iter = (int)((0.95)*fractal->getMaxIter());
			fractal->setMaxIter( new_max_iter <= 50 ? 50 : new_max_iter );
			//DEBUG
			cout << "Zoom-out: " << fractal->getMaxIter() << endl;
		}
		//Center
		else if(event->key.keysym.sym == SDLK_c)
		{
			//TODO
			/*
			complex<double> new_center = fractal->GetComplexFromPixel(
				last_mouse_click.first, last_mouse_click.second);
			
			complex<double> new_z_top_left = fractal->GetComplexFromPixel(
				);
			complex<double> new_z_bottom_right = ;
			*/
		}
		
	}
	//See http://www.sdltutorials.com/sdl-events for more complex examples
}

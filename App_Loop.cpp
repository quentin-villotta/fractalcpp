#include "App.h"

void App::Loop()
{
	//Auto-zoom
	//SDL_Delay(100);
	//complex<double> hippo(-0.743643, 0.13182590);
	//fractal->ZoomView(hippo, 0.80);
	
	//Click-zoom
	/*
	int x = last_mouse_click.first;
	int y = last_mouse_click.second;
	complex<double> z_top_left = fractal->z_top_left;
	complex<double> z_bottom_right = fractal->z_bottom_right;
	int width = width_display;
	int height = height_display;
	
	complex<double> new_center(z_top_left.real() + x * (z_bottom_right.real() -
		z_top_left.real()) / (width - 1), z_top_left.imag() + y *
		(z_bottom_right.imag() - z_top_left.imag()) / (height - 1));
	
	fractal->ZoomView(new_center, 0.80);
	*/
}

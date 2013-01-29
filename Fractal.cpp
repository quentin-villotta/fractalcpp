#include "Fractal.h"

Fractal::Fractal(int w, int h)
{
	width = w;
	height = h;
	
	matrix_iter = new int[width * height];
	matrix_color = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);
}

Fractal::~Fractal(void)
{
	delete [] matrix_iter;
	SDL_FreeSurface(matrix_color);
}

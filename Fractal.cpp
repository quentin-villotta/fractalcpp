#include "Fractal.h"

Fractal::Fractal(int _width, int _height, int _max_iter = 100)
{
	width = _width;
	height = _height;
	max_iter = _max_iter;

	matrix_iter = new int[width * height];
	matrix_color = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height,
		32, 0, 0, 0, 0);
}

Fractal::~Fractal(void)
{
	delete [] matrix_iter;
	SDL_FreeSurface(matrix_color);
}

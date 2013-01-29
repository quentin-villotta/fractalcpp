#pragma once

#include <complex>

#ifdef __GNUC__
#include <SDL/SDL.h>
#else
#include "SDL.h"
#endif

using namespace std;

class Fractal
{
	protected:
		complex<double> z_top_left, z_bottom_right; //Add z_top_left_old and z_bottom_right for dezooming feature

		int width, height;
	
		int* matrix_iter;
		
	public:
		SDL_Surface* matrix_color;
		
		Fractal(int, int);
		~Fractal(void);

		//bool UpdateIter(new_z_top_left, new_z_bottom_right);
		//bool UpdateColor();
};

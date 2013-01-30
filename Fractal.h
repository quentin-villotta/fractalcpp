/**
 * \class Fractal
 *
 * \brief This class is for storing a view of a fractal.
 *
 * This class computes and stores a part of a fractal defined by a rectangle 
 * of the complex plane. More precisly it stores the number of iterations needed
 * to be outside the fractal, and the corresponding colors in an SDL_Surface. 
 *
 */
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
		complex<double> z_top_left, z_bottom_right;
		
		int width, height;
		int max_iter;
		int* matrix_iter;
		
	public:
		SDL_Surface* matrix_color;
		
		Fractal(int, int, int, complex<double>, complex<double>);
		~Fractal(void);

		/// TODO
		//ChangeView(complex<double> z_top_left, complex<double> z_bottom_right)
		
		/// Compute a new view of the fractal given a rectangle
		virtual void UpdateIter() = 0;
		
		/// Colorize the fractal based on the number of iteration
		virtual void UpdateColor() = 0;
};

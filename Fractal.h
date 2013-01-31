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
		complex<double> orbit;

		int width, height;
		int max_iter;
		
		int* matrix_iter;
		SDL_Surface* matrix_color;

	public:	
		Fractal(int, int, int, complex<double>, complex<double>);
		~Fractal(void);
		SDL_Surface* getMatrixColor(void);

		/// TODO
		//ChangeView(complex<double> z_top_left, complex<double> z_bottom_right)

		/// Compute the number of iteration required for a serie starting at z0 with orbit c
		int CalculateNbIterations (complex<double>, complex<double>);
	
	private:
		/// Compute a new view of the fractal given a rectangle
		virtual void UpdateIter() = 0;
		
		/// Colorize the fractal based on the number of iteration
		virtual void UpdateColor() = 0;
};

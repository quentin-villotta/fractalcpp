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

#include "SurfaceHelper.h"

using namespace std;

class Fractal
{
	protected:
		complex<double> z_top_left, z_bottom_right;
		complex<double> orbit;

		int width, height;
		int max_iter;
		
		int* matrix_iter;
		complex<double>* matrix_lastTerm;
		SDL_Surface* matrix_color;
		
		/// Colorize the fractal based on the number of iteration
		void UpdateColor( );
		void ColorTimeEscapeDarkRGB (int, int, Uint8*);
		void ColorTimeEscapeBlueDarkRGB (int, int, Uint8*);
		void ColorTimeEscapeBlackWhiteRGB (int, int, Uint8*);
		void ColorTimeEscapeBlackWhiteBisRGB (int, int, Uint8*);
		void ColorSmoothDarkRGB (int, int, Uint8*);

		/// Compute a new view of the fractal given a rectangle
		virtual void UpdateIter() = 0;
		
	public:	
		Fractal(int, int, int, complex<double>, complex<double>);
		~Fractal(void);
		
		SDL_Surface* getMatrixColor(void);
		void setMaxIter(int);
		int getMaxIter();

		complex<double> GetComplexFromPixel(int, int);
		
		// Change the current view of the fractal by recalculating
		void ChangeView(complex<double>, complex<double>);
		
		void ZoomView(complex<double>, double);

		/// Compute the number of iteration required for a serie starting at z0 with orbit c
		int CalculateNbIterations (complex<double>&, complex<double>);
};

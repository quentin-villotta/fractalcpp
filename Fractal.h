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
#include "ColorFunction.h"

using namespace std;

class Fractal
{
protected:
	/// Parameters defining the window bounds
	complex<double> z_top_left, z_bottom_right;

	/// Parameters defining the window resolution
	int width, height;

	/// Initial and current number of maximum iteration
	int max_iter_default;
	int max_iter;
		
	/// Complex value of the orbit in order to generate the set
	complex<double> orbit;

	/// Matrix storing, for each point, the number of iterations
	int* matrix_iter;
		
	/// Matrix storing, for each point, the value of the last term
	complex<double>* matrix_last_term;
		
	/// Matrix storing, for each point, the color code
	SDL_Surface* matrix_color;
		
public:	
	/// Constructor and destructor
	Fractal(int, int, int, complex<double>, complex<double>);
	~Fractal(void);
		
	/// Accessors and setters
	SDL_Surface* GetMatrixColor(void);
	void SetMaxIter(int);
	int GetMaxIter();
	int GetMaxIterDefault();

	/// Get the complex nomber from the pixel on the screen
	complex<double> GetComplexFromPixel(int, int);
		
	/// Change the current view of the fractal by recalculating
	void ChangeView(complex<double>, complex<double>, class ColorFunction&);
		
	/// Zoom
	void ZoomView(complex<double>, double, class ColorFunction&);

	/// Colorize the fractal based on the number of iteration
	void UpdateColor(class ColorFunction&);

	/// Compute the number of iteration required for a sequence starting at z0 with orbit c
	int CalculateNbIterations (complex<double>&, complex<double>);

	/// Compute a new view of the fractal given a rectangle
	virtual void UpdateIter() = 0;
		
	/// Read-only accessors
	const complex<double>& _z_top_left() const {return z_top_left;}
	const complex<double>& _z_bottom_right() const {return z_bottom_right;}
};

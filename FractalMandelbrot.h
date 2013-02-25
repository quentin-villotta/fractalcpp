/**
 * \class FractalMandelbrot
 *
 * \brief This class inheritates from the class Fractal.
 *
 * This class implements the method "UpdateIter" in order to generate
 * the Mandelbrot set.
 *
 */
#pragma once

#include <complex>
#include <iostream>

#include "Fractal.h"

using namespace std;

class FractalMandelbrot : public Fractal
{
public:
	/// Constructor and destructor
	FractalMandelbrot(int, int, int, complex<double>, complex<double>, class ColorFunction&);
	~FractalMandelbrot(void);

private:
	/// Implementation of the method generating the Mandelbrot set
	virtual void UpdateIter();
};


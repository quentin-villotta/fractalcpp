#pragma once

#include <complex>
#include <iostream>

#include "Fractal.h"

using namespace std;

class FractalMandelbrot : public Fractal
{
	public:
		FractalMandelbrot(int, int, int, complex<double>, complex<double>, class ColorFunction&);
		~FractalMandelbrot(void);

	private:
		virtual void UpdateIter();
};


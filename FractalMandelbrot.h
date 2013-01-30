#pragma once

#include <complex>
#include <iostream>

#include "Fractal.h"
#include "SurfaceHelper.h"

using namespace std;

class FractalMandelbrot : public Fractal
{
public:
	FractalMandelbrot(int, int, int, complex<double>, complex<double>);
	~FractalMandelbrot(void);

	virtual void UpdateIter();
	virtual void UpdateColor();
};


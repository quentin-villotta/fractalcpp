#pragma once

#include <complex>
#include <iostream>

#include "Fractal.h"
#include "SurfaceHelper.h"

using namespace std;

class FractalMandelbrot : public Fractal
{
public:
	FractalMandelbrot(int, int, int);
	~FractalMandelbrot(void);

	virtual void UpdateIter(complex<double>, complex<double>);
	virtual void UpdateColor();
};


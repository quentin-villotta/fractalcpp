#pragma once
#include "Fractal.h"

class FractalMandelbrot : public Fractal
{
public:
	FractalMandelbrot(int, int, int);
	~FractalMandelbrot(void);

	virtual void UpdateIter(complex<double>, complex<double>);
	virtual void UpdateColor();
};


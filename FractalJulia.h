#pragma once
#include "Fractal.h"
#include "SurfaceHelper.h"

#include <complex>

using namespace std;

class FractalJulia : public Fractal
{
protected:
	complex<double> orbit;

public:
	//TODO : add orbit as argument to constructor
    FractalJulia(int, int, int, complex<double>, complex<double>);
	~FractalJulia(void);

	//void UpdateIter(complex<double>, complex<double>, complex<double>);
	//virtual void UpdateColor();
};


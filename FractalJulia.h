#pragma once
#include "Fractal.h"
#include "SurfaceHelper.h"

#include <complex>

using namespace std;

class FractalJulia : public Fractal
{
protected:
	

public:
	//TODO : add orbit as argument to constructor
    FractalJulia(int, int, int, complex<double>, complex<double>);
	~FractalJulia(void);

	virtual void UpdateIter();
	virtual void UpdateColor();
};


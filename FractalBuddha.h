#pragma once
#include "Fractal.h"
#include "SurfaceHelper.h"

#include <complex>

using namespace std;

class FractalBuddha : public Fractal
{
protected:
	long maxRandom;

public:
	FractalBuddha(int, int, int, complex<double>, complex<double>);
	~FractalBuddha(void);

	virtual void UpdateIter();
};


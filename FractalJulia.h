#pragma once
#include "Fractal.h"

#include <complex>

using namespace std;

class FractalJulia : public Fractal
{
	public:
    	FractalJulia(int, int, int, complex<double>, complex<double>, complex<double>, class ColorFunction&);
		~FractalJulia(void);

	private:
		virtual void UpdateIter();
};


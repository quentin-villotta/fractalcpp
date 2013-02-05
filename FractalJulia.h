#pragma once
#include "Fractal.h"

#include <complex>

using namespace std;

class FractalJulia : public Fractal
{
	public:
		//TODO : add orbit as argument to constructor
    	FractalJulia(int, int, int, complex<double>, complex<double>, complex<double>, class ColorFunction&);
		~FractalJulia(void);

	private:
		virtual void UpdateIter();
};


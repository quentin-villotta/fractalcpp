#pragma once

#ifdef __GNUC__
#include <SDL/SDL.h>
#else
#include "SDL.h"
#endif

#include <complex>
using namespace std;

class ColorFunction 
{
public:
	ColorFunction(void) {};
	virtual ~ColorFunction(void) {};
	virtual void Value (int, int, complex<double>, Uint8*)=0;
};

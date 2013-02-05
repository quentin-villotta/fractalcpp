#pragma once

#include "ColorFunction.h"

#include <complex>

using namespace std;

class ColorTimeEscapeDarkRGB : public ColorFunction
{
public:
	ColorTimeEscapeDarkRGB(void) {};
	~ColorTimeEscapeDarkRGB(void) {};
	
	void Value(int iteration, int max_iter, complex<double> lastTerm,
			   Uint8* tabColors)
	{ 
		double color = (iteration - log(log(abs(lastTerm) )))/max_iter;
		if (iteration == max_iter)
		{
			tabColors[0] = (Uint8) (0);
			tabColors[1] = (Uint8) (0);
			tabColors[2] = (Uint8) (0);
		}
		else
		{
			tabColors[0] = (Uint8) (255.0 * color);
			tabColors[1] = (Uint8) (255.0 * color);
			tabColors[2] = (Uint8) (255.0 * color);
		}
	};
};

#pragma once

#include "ColorFunction.h"

#include <complex>

using namespace std;

class ColorBlackBlue : public ColorFunction 
{
public:
	ColorBlackBlue(void) {};
	~ColorBlackBlue(void) {};

	void Value (int iterations, int max_iter, complex<double> lastTerm, 
				Uint8* tabColors)
	{

		if (iterations == max_iter)
		{
			tabColors[0] = (Uint8) (0);
			tabColors[1] = (Uint8) (0);
			tabColors[2] = (Uint8) (0);
		}
		else
		{
			tabColors[0] = (Uint8) (0);
			tabColors[1] = (Uint8) (0);
			tabColors[2] = (Uint8) (255.0 * (double) (iterations) / 
				(double) max_iter);
		}
	};
};

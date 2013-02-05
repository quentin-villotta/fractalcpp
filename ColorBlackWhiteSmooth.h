#pragma once

#include "ColorFunction.h"

#include <complex>

using namespace std;

class ColorBlackWhiteSmooth : public ColorFunction 
{
public:
	ColorBlackWhiteSmooth(void) {};
	~ColorBlackWhiteSmooth(void) {};

	void Value (int iterations, int max_iter, complex<double> lastTerm,
				Uint8* tabColors)
	{
		double color = (iterations - log(log(abs(lastTerm) )))/max_iter;

		if (iterations == max_iter)
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

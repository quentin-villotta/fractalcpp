#pragma once

#include "ColorFunction.h"

#include <complex>

using namespace std;

class ColorBlackWhiteMod : public ColorFunction
{
public:
	ColorBlackWhiteMod(void) {};
	~ColorBlackWhiteMod(void) {};

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
			if ((iterations%2) == 0)
			{
				tabColors[0] = (Uint8) (0);
				tabColors[1] = (Uint8) (0);
				tabColors[2] = (Uint8) (0);
			}
			else
			{
				tabColors[0] = (Uint8) (255);
				tabColors[1] = (Uint8) (255);
				tabColors[2] = (Uint8) (255);
			}
		}
	};
};

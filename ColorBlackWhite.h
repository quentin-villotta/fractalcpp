#pragma once

#include "ColorFunction.h"

#include <complex>

using namespace std;

class ColorBlackWhite : public ColorFunction
{
public:
	/// Constructor and destructor
	ColorBlackWhite(void) {};
	~ColorBlackWhite(void) {};

	/// Function calculating the RGB color code
	void Value(int iterations, int max_iter, complex<double> lastTerm, 
			   Uint8* tabColors)
	{
		// If the complex point belongs to the set
		if (iterations == max_iter)
		{
			tabColors[0] = (Uint8) (0);
			tabColors[1] = (Uint8) (0);
			tabColors[2] = (Uint8) (0);
		}
		// Else, we calculate a color gradient from black to white
		else
		{
			tabColors[0] = (Uint8) (255.0 * (double) (iterations) / 
				(double) max_iter);
			tabColors[1] = (Uint8) (255.0 * (double) (iterations) / 
				(double) max_iter);
			tabColors[2] = (Uint8) (255.0 * (double) (iterations) / 
				(double) max_iter);
		}
	};
};

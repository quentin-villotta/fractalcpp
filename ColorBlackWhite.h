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
	void Value(int iterations, int max_iter, complex<double> last_term, 
				Uint8* tab_colors)
	{
		// If the complex point belongs to the set
		if (iterations == max_iter)
		{
			tab_colors[0] = (Uint8) (0);
			tab_colors[1] = (Uint8) (0);
			tab_colors[2] = (Uint8) (0);
		}
		// Else, we calculate a color gradient from black to white
		else
		{
			tab_colors[0] = (Uint8) (255.0 * (double) (iterations) / 
				(double) max_iter);
			tab_colors[1] = (Uint8) (255.0 * (double) (iterations) / 
				(double) max_iter);
			tab_colors[2] = (Uint8) (255.0 * (double) (iterations) / 
				(double) max_iter);
		}
	};
};

#pragma once

#include "ColorFunction.h"

#include <complex>

using namespace std;

class ColorBlackWhiteMod : public ColorFunction
{
	public:
		/// Constructor and destructor
		ColorBlackWhiteMod(void) {};
		~ColorBlackWhiteMod(void) {};

		/// Function calculating the RGB color code
		void Value (int iterations, int max_iter, complex<double> last_term, 
					Uint8* tab_colors)
		{
			// If the complex point belongs to the set
			if (iterations == max_iter)
			{
				tab_colors[0] = (Uint8) (0);
				tab_colors[1] = (Uint8) (0);
				tab_colors[2] = (Uint8) (0);
			}
			// The point is black if the number of iteration is even,
			// and white else
			else
			{
				if ((iterations%2) == 0)
				{
					tab_colors[0] = (Uint8) (0);
					tab_colors[1] = (Uint8) (0);
					tab_colors[2] = (Uint8) (0);
				}
				else
				{
					tab_colors[0] = (Uint8) (255);
					tab_colors[1] = (Uint8) (255);
					tab_colors[2] = (Uint8) (255);
				}
			}
		};
};

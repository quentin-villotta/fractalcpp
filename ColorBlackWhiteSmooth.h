#pragma once

#include "ColorFunction.h"

#include <complex>

using namespace std;

class ColorBlackWhiteSmooth : public ColorFunction 
{
	public:
		/// Constructor and destructor
		ColorBlackWhiteSmooth(void) {};
		~ColorBlackWhiteSmooth(void) {};

		/// Function calculating the RGB color code
		void Value (int iterations, int max_iter, complex<double> last_term,
					Uint8* tab_colors)
		{
			// We calculate a smooth color code which is function of the number
			// of iteration done and the value of the last term in the sequence
			double color = (iterations - log(log(abs(last_term) )))/max_iter;

			// If the complex point belongs to the set
			if (iterations == max_iter)
			{
				tab_colors[0] = (Uint8) (0);
				tab_colors[1] = (Uint8) (0);
				tab_colors[2] = (Uint8) (0);
			}
			else
			{
				tab_colors[0] = (Uint8) (255.0 * color);
				tab_colors[1] = (Uint8) (255.0 * color);
				tab_colors[2] = (Uint8) (255.0 * color);
			}
		};
};

/**
 * \class ColorFunction
 *
 * \brief This abstract class stands for color functions.
 *
 * This class contains an abstract method "Value" for calculating an
 * RGB color code which is function of the parameters : 
 *		- number of iterations for the complex point ;
 *		- maximal number of iterations allowed ;
 *		- value of the last complex term calculated in the sequence.
 *
 * The result is stored in a 3 dimension array which MUST be allocated before.
 * The 3 dimensions stands for (R,G,B) color code, and the type used is Uint8
 * (in order to use the SDL library).
 */
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
		/// Constructor and destructor
		ColorFunction(void) {};
		virtual ~ColorFunction(void) {};

		/// Function calculating the RGB color code
		virtual void Value (int, int, complex<double>, Uint8*)=0;
};

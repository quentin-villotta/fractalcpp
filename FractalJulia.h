/**
 * \class FractalJulia
 *
 * \brief This class inheritates from the class Fractal.
 *
 * This class implements the method "UpdateIter" in order to generate
 * the Julia set.
 *
 */
#pragma once
#include "Fractal.h"

#include <complex>

using namespace std;

class FractalJulia : public Fractal
{
	public:
		/// Constructor and destructor
    	FractalJulia(int, int, int, complex<double>, complex<double>, complex<double>, class ColorFunction&);
		~FractalJulia(void);

	private:
		/// Implementation of the method generating the Julia set
		virtual void UpdateIter();
};


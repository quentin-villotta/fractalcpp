#include "FractalBuddha.h" 

FractalBuddha::FractalBuddha(int _width, int _height, int _max_iter,
	complex<double> _z_top_left, complex<double> _z_bottom_right) :
	Fractal(_width, _height, _max_iter, _z_top_left, _z_bottom_right)
{
	maxRandom = 10000;
}

void FractalBuddha::UpdateIter()
{
	for(long M=0 ; M<maxRandom ; M++) {
		orbit; // faire un rand
		int iterations = CalculateNbIterations (orbit, orbit);
		
	}
}
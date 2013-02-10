#include "FractalJulia.h" 

FractalJulia::FractalJulia(int _width, int _height, int _max_iter,
	complex<double> _z_top_left, complex<double> _z_bottom_right, 
	complex<double> _orbit, class ColorFunction& funTocolor) :
	Fractal(_width, _height, _max_iter, _z_top_left, _z_bottom_right)
{
	orbit = _orbit;
	UpdateIter();
	UpdateColor( funTocolor );
}


FractalJulia::~FractalJulia(void) {}

void FractalJulia::UpdateIter()
{
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			complex<double> z = GetComplexFromPixel(x, y);
			
			matrix_iter[y * width + x] = CalculateNbIterations(z, orbit);
			matrix_lastTerm[y * width + x] = z;
		}
	}
}

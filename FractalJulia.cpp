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
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			// For each complex point in the window
			complex<double> z = GetComplexFromPixel(x, y);
			
			// Storing in matrices the number of iterations and the value of the last term
			matrix_iter[y * width + x] = CalculateNbIterations(z, orbit);
			matrix_last_term[y * width + x] = z;
		}
	}
}

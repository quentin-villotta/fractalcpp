#include "FractalJulia.h" 

FractalJulia::FractalJulia(int _width, int _height, int _max_iter,
	complex<double> _z_top_left, complex<double> _z_bottom_right, complex<double> _orbit) :
	Fractal(_width, _height, _max_iter, _z_top_left, _z_bottom_right)
{
	//orbit = complex<double>(0.72, 0.11);
	//orbit = complex<double>(0.835, -0.2321);
	orbit = _orbit; // Nice one
	//orbit = complex<double>(0.4, 0.6);
	//orbit = complex<double>(0.8, 0.156);
	UpdateIter();
	UpdateColor( );
}


FractalJulia::~FractalJulia(void)
{
}

void FractalJulia::UpdateIter()
{
	for(int x = 0; x < width; x++)
		for(int y = 0; y < height; y++)
		{
			complex<double> z = GetComplexFromPixel(x, y);
			
			matrix_iter[y * width + x] = CalculateNbIterations(z, orbit);
			matrix_lastTerm[y * width + x] = z;
		}
}

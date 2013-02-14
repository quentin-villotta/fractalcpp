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
			/*complex<double> z(z_top_left.real() + x * (z_bottom_right.real() -
				z_top_left.real()) / (width - 1), z_top_left.imag() + y *
				(z_bottom_right.imag() - z_top_left.imag()) / (height - 1));*/
			complex<double> z = GetComplexFromPixel(x, y);
			
			int i = 0;			
			for(; i < max_iter && norm(z) < 4.0; i++)
				z = z * z + orbit;
			
			matrix_iter[y * width + x] = i;
			matrix_lastTerm[y * width + x] = z;
		}
	}
}

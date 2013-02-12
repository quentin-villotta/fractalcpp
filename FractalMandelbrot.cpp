#include "FractalMandelbrot.h"

FractalMandelbrot::FractalMandelbrot(int _width, int _height, int _max_iter,
	complex<double> _z_top_left, complex<double> _z_bottom_right,
	class ColorFunction& funTocolor) :
	Fractal(_width, _height, _max_iter, _z_top_left, _z_bottom_right )
{
	UpdateIter();
	UpdateColor( funTocolor );
}

FractalMandelbrot::~FractalMandelbrot(void) {}

void FractalMandelbrot::UpdateIter()
{
	//int x, y;
	complex<double> z;
	
	#pragma omp parallel for
	for(int x = 0; x < width; x++)
	{
		///*DEBUG*/printf("Thread id: %d\n", omp_get_thread_num());
		for(int y = 0; y < height; y++) {
			z = GetComplexFromPixel(x, y);
			
			matrix_iter[y * width + x] = CalculateNbIterations (z, z);
			matrix_lastTerm[y * width + x] = z;
		}
	}
}

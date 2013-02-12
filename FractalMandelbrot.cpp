#include "FractalMandelbrot.h"

FractalMandelbrot::FractalMandelbrot(int _width, int _height, int _max_iter,
	complex<double> _z_top_left, complex<double> _z_bottom_right,
	class ColorFunction& funTocolor) :
	Fractal(_width, _height, _max_iter, _z_top_left, _z_bottom_right )
{
	boost::timer t; // start timing
	
	UpdateIter();
	
	cout << "Computing time: " << t.elapsed() << "s" << endl;
	
	UpdateColor( funTocolor );
	
}

FractalMandelbrot::~FractalMandelbrot(void) {}

void FractalMandelbrot::UpdateIter()
{
	// 7.5 sec without parallelization
	// 15 sec with "pragma omp parallel"
	// 7.5 sec with "pragma omp parallel for"
	
	//printf("Number of threads: %d\n", omp_get_num_threads());
	
	int x, y;
	complex<double> z;
	
	int* _matrix_iter = matrix_iter;
	complex<double>* _matrix_lastTerm = matrix_lastTerm;
	
	int _width = width;
	int _height = height;
	
	printf("NCPU=%d\n", omp_get_num_procs());
	printf("NTHREAD=%d\n", omp_get_num_threads());
	
	#pragma omp parallel for num_threads(2) private(x, y, z) shared(_matrix_iter, _matrix_lastTerm, _width, _height)
	for(x = 0; x < _width; x++)
	{
		///*DEBUG*/printf("Thread id: %d\n", omp_get_thread_num());
		for(y = 0; y < _height; y++)
		{
			z = GetComplexFromPixel(x, y);
			
			_matrix_iter[y * _width + x] = CalculateNbIterations (z, z);
			_matrix_lastTerm[y * _width + x] = z;
		}
	}
}

#include "FractalMandelbrot.h"

FractalMandelbrot::FractalMandelbrot(int _width, int _height, int _max_iter,
	complex<double> _z_top_left, complex<double> _z_bottom_right,
	class ColorFunction& funTocolor) :
	Fractal(_width, _height, _max_iter, _z_top_left, _z_bottom_right )
{
	//boost::timer t; // start timing
	
	UpdateIter();
	
	//cout << "Computing time: " << t.elapsed() << "s" << endl;
	
	UpdateColor( funTocolor );
	
}

FractalMandelbrot::~FractalMandelbrot(void) {}

void FractalMandelbrot::UpdateIter()
{
	// 7.5 sec without parallelization
	// 15 sec with "pragma omp parallel"
	// 7.5 sec with "pragma omp parallel for"
	
	
	//omp_set_dynamic(1); // let OpenMP choose an appropriate number of threads
	
	#pragma omp parallel for private(y,i)
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			complex<double> z(z_top_left.real() + x * (z_bottom_right.real() -
				z_top_left.real()) / (width - 1), z_top_left.imag() + y *
				(z_bottom_right.imag() - z_top_left.imag()) / (height - 1));
			
			complex<double> z_init = z;
			int i;
			
			for(i = 0; i < max_iter && norm(z) < 4.0; i++)
				z = z * z + z_init;
			
			matrix_iter[y * width + x] = i;
			matrix_lastTerm[y * width + x] = z;
		}
	}
	

	/*
	const int height = img.height; // OpenMP needs signed integrals for loop counters

	#pragma omp parallel for shared(img, domain) 
	for (int y = 0; y < height; ++y)
	{
	    const double pos_y = lerp(double(y) / img.height, domain[0].imag(), domain[1].imag());
	    for (size_t x = 0; x != img.width; ++x)
	    {
	        const double pos_x = lerp(double(x) / img.width, domain[0].real(), domain[1].real());
	        img(x, y) = mandelbrot(complex_t(pos_x, pos_y)); // colour the pixel
	    }
	}
	*/
}

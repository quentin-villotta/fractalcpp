#include "FractalMandelbrot.h"


FractalMandelbrot::FractalMandelbrot(int _width, int _height, int _max_iter) : Fractal(_width, _height, _max_iter)
{
}

FractalMandelbrot::~FractalMandelbrot(void)
{
}

void FractalMandelbrot::UpdateIter(complex<double> z_top_left_new, complex<double> z_bottom_right_new) {
	// For each couple (a, b), we will calculate the number of iteration required
	double a, b;
	double x_n, y_n;
	int nb_iteration;
	double temp;
	
	// For each line
	for (int i=0 ; i<height ; i++) {
		b = z_top_left_new.imag() + i * (z_bottom_right_new.imag() - z_top_left_new.imag()) / (height-1);
		// For each column
		for (int j=0 ; j<width ; j++) {
			a = z_top_left_new.real() + j * (z_bottom_right_new.real()-z_top_left_new.real()) / (width-1);
			
			// Iterations required for the point (a,b)
			x_n = 0;
			y_n = 0;
			nb_iteration = 0;
			
			do {
				temp = x_n;
				x_n = x_n*x_n - y_n*y_n + a;
				y_n = 2*y_n*temp + b;
				nb_iteration++;
			}
			while (nb_iteration<max_iter && (x_n*x_n + y_n*y_n < 4));

			matrix_iter[(i-1)*width + j] = nb_iteration;
		}
	}
}

void FractalMandelbrot::UpdateColor()
{
	
}

#include "FractalMandelbrot.h"

FractalMandelbrot::FractalMandelbrot(int _width, int _height, int _max_iter,
	complex<double> _z_top_left, complex<double> _z_bottom_right) :
	Fractal(_width, _height, _max_iter, _z_top_left, _z_bottom_right)
{
}

FractalMandelbrot::~FractalMandelbrot(void)
{
}

void FractalMandelbrot::UpdateIter()
{
	for(int x = 0; x < width; x++)
		for(int y = 0; y < height; y++)
		{
			complex<double> c(z_top_left.real() + x * (z_bottom_right.real() -
				z_top_left.real()) / (width - 1), z_top_left.imag() + y *
				(z_bottom_right.imag() - z_top_left.imag()) / (height - 1));
			complex<double> z(0.0, 0.0);
			int iterations;
			
			for(iterations = 0; iterations < max_iter && norm(z) < 4.0; iterations++)
				z = z * z + c;
			
			matrix_iter[y * width + x] = iterations;
		}
}

void FractalMandelbrot::UpdateColor()
{
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			int iter = matrix_iter[y * width + x];
			
			//if (x,y) belongs to Mandelbrot's set
			if(iter == max_iter)
				SurfaceHelper::PutPixelRGB(matrix_color, x, y, 0, 0, 0);
			else
			{
				double rate_iter = (double) (iter) / (double) max_iter;
				Uint8 color_code = (Uint8) (255.0 * rate_iter);
				SurfaceHelper::PutPixelRGB(matrix_color, x, y, color_code, color_code, color_code);
			}
		}
	}	
}


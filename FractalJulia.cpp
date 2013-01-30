#include "FractalJulia.h" 

FractalJulia::FractalJulia(int _width, int _height, int _max_iter,
	complex<double> _z_top_left, complex<double> _z_bottom_right) :
	Fractal(_width, _height, _max_iter, _z_top_left, _z_bottom_right)
{
	orbit = complex<double>(0.72, 0.11);
}


FractalJulia::~FractalJulia(void)
{
}

/*
void FractalJulia::UpdateIterJulia(complex<double> z_top_left_new, complex<double> z_bottom_right_new, complex<double> orbit)
{
	for(int x = 0; x < width; x++)
		for(int y = 0; y < height; y++)
		{
			complex<double> c(z_top_left_new.real() + x * (z_bottom_right_new.real() - z_top_left_new.real()) / (width - 1),
				z_top_left_new.imag() + y * (z_bottom_right_new.imag() - z_top_left_new.imag()) / (height - 1));
			complex<double> z = c;
			int iterations;
			
			for(iterations = 0; iterations < max_iter && norm(z) < 4.0; iterations++)
				z = z * z + orbit;
			
			matrix_iter[y * width + x] = iterations;
		}
}

void FractalJulia::UpdateColor()
{
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			int iter = matrix_iter[y * width + x];
			
			//if (x,y) belongs to Julia's set
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
*/
#include "FractalJulia.h" 

FractalJulia::FractalJulia(int _width, int _height, int _max_iter,
	complex<double> _z_top_left, complex<double> _z_bottom_right) :
	Fractal(_width, _height, _max_iter, _z_top_left, _z_bottom_right)
{
	//orbit = complex<double>(0.72, 0.11);
	//orbit = complex<double>(0.835, -0.2321);
	orbit = complex<double>(0.285, 0.01); // Nice one
	//orbit = complex<double>(0.4, 0.6);
	//orbit = complex<double>(0.8, 0.156);
	UpdateIter();
	UpdateColor();
}


FractalJulia::~FractalJulia(void)
{
}

void FractalJulia::UpdateIter()
{
	for(int x = 0; x < width; x++)
		for(int y = 0; y < height; y++)
		{
			complex<double> z (z_top_left.real() + x * (z_bottom_right.real() -
				z_top_left.real()) / (width - 1), z_top_left.imag() + y *
				(z_bottom_right.imag() - z_top_left.imag()) / (height - 1));
			
			matrix_iter[y * width + x] = CalculateNbIterations(z, orbit);
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

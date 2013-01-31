#include "Fractal.h"

Fractal::Fractal(int _width, int _height, int _max_iter, 
	complex<double> _z_top_left, complex<double> _z_bottom_right)
{
	width = _width;
	height = _height;
	
	max_iter = _max_iter;
	
	z_top_left = _z_top_left;
	z_bottom_right = _z_bottom_right;

	matrix_iter = new int[width * height];
	matrix_color = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height,
		32, 0, 0, 0, 0);
}

Fractal::~Fractal(void)
{
	delete [] matrix_iter;
	SDL_FreeSurface(matrix_color);
}

SDL_Surface* Fractal::getMatrixColor(void)
{
	return matrix_color;
}

int Fractal::CalculateNbIterations(complex<double> z, complex<double> orbit)
{
	int iterations;
	for(iterations = 0; iterations < max_iter && norm(z) < 4.0; iterations++)
		z = z * z + orbit;
	return iterations;
}

void Fractal::ChangeView(complex<double> z_top_left_new, 
	complex<double> z_bottom_right_new)
{
	z_top_left = z_top_left_new;
	z_bottom_right = z_bottom_right_new;
	UpdateIter();
	UpdateColor();
}

void Fractal::UpdateColor()
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

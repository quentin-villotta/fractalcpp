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

void Fractal::ZoomView(complex<double> center, double zoom_scale)
{
	double cur_width = z_bottom_right.real() - z_top_left.real();
	double cur_height = z_top_left.imag() - z_bottom_right.imag();
	
	double new_width = zoom_scale * cur_width;
	double new_height = zoom_scale * cur_height;
	
	complex<double> translate_top_left(- new_width / 2, new_height / 2);
	complex<double> translate_bottom_right(new_width / 2, - new_height / 2);	
	
	ChangeView(center + translate_top_left, center + translate_bottom_right);
}

void Fractal::UpdateColor()
{
	Uint8* tabColors = new Uint8[3];

	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			int iter = matrix_iter[y * width + x];
			ColorTimeEscapeBlueDarkRGB(iter, tabColors);

			SurfaceHelper::PutPixelRGB(matrix_color, x, y, tabColors[0], tabColors[1], tabColors[2]);

			/*
			//if (x,y) belongs to Mandelbrot's set
			if(iter == max_iter)
				SurfaceHelper::PutPixelRGB(matrix_color, x, y, 0, 0, 0);
			else
			{
				double rate_iter = (double) (iter) / (double) max_iter;
				Uint8 color_code = (Uint8) (255.0 * rate_iter);
				SurfaceHelper::PutPixelRGB(matrix_color, x, y, color_code, color_code, color_code);
			} */
		}
	}
	delete tabColors;
}

void Fractal::ColorTimeEscapeDarkRGB (int iteration, Uint8* tabColors) {
	if (iteration == max_iter) {
		tabColors[0] = (Uint8) (0);
		tabColors[1] = (Uint8) (0);
		tabColors[2] = (Uint8) (0);
	}
	else {
		tabColors[0] = (Uint8) (255.0 * (double) (iteration) / (double) max_iter);
		tabColors[1] = (Uint8) (255.0 * (double) (iteration) / (double) max_iter);
		tabColors[2] = (Uint8) (255.0 * (double) (iteration) / (double) max_iter);
	}
}

void Fractal::ColorTimeEscapeBlueDarkRGB (int iteration, Uint8* tabColors) {
	if (iteration == max_iter) {
		tabColors[0] = (Uint8) (0);
		tabColors[1] = (Uint8) (0);
		tabColors[2] = (Uint8) (0);
	}
	else {
		tabColors[0] = (Uint8) (0);
		tabColors[1] = (Uint8) (0);
		tabColors[2] = (Uint8) (255.0 * (double) (iteration) / (double) max_iter);
	}
}

void Fractal::ColorTimeEscapeBlackWhiteRGB (int iteration, Uint8* tabColors) {
	if (iteration == max_iter) {
		tabColors[0] = (Uint8) (0);
		tabColors[1] = (Uint8) (0);
		tabColors[2] = (Uint8) (0);
	}
	else {
		if ((iteration%2) == 0) {
			tabColors[0] = (Uint8) (0);
			tabColors[1] = (Uint8) (0);
			tabColors[2] = (Uint8) (0);
		}
		else {
			tabColors[0] = (Uint8) (255);
			tabColors[1] = (Uint8) (255);
			tabColors[2] = (Uint8) (255);
		}
	}
}
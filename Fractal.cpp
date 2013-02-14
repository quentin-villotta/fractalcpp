#include "Fractal.h"

/// Fractal Class
Fractal::Fractal(int _width, int _height, int _max_iter, 
	complex<double> _z_top_left, complex<double> _z_bottom_right)
{
	width = _width;
	height = _height;
	
	max_iter = _max_iter;
	
	z_top_left = _z_top_left;
	z_bottom_right = _z_bottom_right;

	matrix_iter = new int[width * height];
	matrix_lastTerm = new complex<double>[width * height];

	matrix_color = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height,
		32, 0, 0, 0, 0);
}

Fractal::~Fractal(void)
{
	delete [] matrix_iter;
	delete [] matrix_lastTerm;

	SDL_FreeSurface(matrix_color);
}

void Fractal::SetMaxIter(int new_max_iter)
{
	max_iter = new_max_iter;
}

int Fractal::GetMaxIter()
{
	return max_iter;
}

SDL_Surface* Fractal::GetMatrixColor(void)
{
	return matrix_color;
}

complex<double> Fractal::GetComplexFromPixel(int x, int y)
{
       complex<double> z(z_top_left.real() + x * (z_bottom_right.real() -
               z_top_left.real()) / (width - 1), z_top_left.imag() + y *
               (z_bottom_right.imag() - z_top_left.imag()) / (height - 1));
       return z;
}

void Fractal::ChangeView(complex<double> z_top_left_new, 
	complex<double> z_bottom_right_new, class ColorFunction& funTocolor)
{
	z_top_left = z_top_left_new;
	z_bottom_right = z_bottom_right_new;
	UpdateIter();
	UpdateColor( funTocolor );
}

void Fractal::ZoomView(complex<double> center, double zoom_scale, class ColorFunction& funTocolor)
{
	double cur_width = z_bottom_right.real() - z_top_left.real();
	double cur_height = z_top_left.imag() - z_bottom_right.imag();
	
	double new_width = (1.0 - zoom_scale) * cur_width;
	double new_height = (1.0 - zoom_scale) * cur_height;
	
	complex<double> translate_top_left(- new_width / 2, new_height / 2);
	complex<double> translate_bottom_right(new_width / 2, - new_height / 2);	
	
	ChangeView(center + translate_top_left, center + translate_bottom_right, funTocolor);
}


void Fractal::UpdateColor( class ColorFunction& funTocolor )
{
	Uint8* tabColors = new Uint8[3];

	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			int iteration = matrix_iter[y * width + x];
			complex<double> lastTerm = matrix_lastTerm[y * width + x];

			funTocolor.Value(iteration, max_iter, lastTerm, tabColors);
			SurfaceHelper::PutPixelRGB(matrix_color, x, y, tabColors[0], tabColors[1], tabColors[2]);
		}
	}
	delete tabColors;
}

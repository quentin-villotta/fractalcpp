#include "Fractal.h"

void Fractal::ColorTimeEscapeDarkRGB (int x, int y, Uint8* tabColors) {
	int iteration = matrix_iter[y * width + x];

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

void Fractal::ColorTimeEscapeBlueDarkRGB (int x, int y, Uint8* tabColors) {
	int iteration = matrix_iter[y * width + x];

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

void Fractal::ColorTimeEscapeBlackWhiteRGB (int x, int y, Uint8* tabColors) {
	int iteration = matrix_iter[y * width + x];

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

void Fractal::ColorTimeEscapeBlackWhiteBisRGB (int x, int y, Uint8* tabColors) {
	int iteration = matrix_iter[y * width + x];
	complex<double> lastTerm = matrix_lastTerm[y * width + x];

	if (iteration == max_iter) {
		tabColors[0] = (Uint8) (0);
		tabColors[1] = (Uint8) (0);
		tabColors[2] = (Uint8) (0);
	}
	else {
		if ((lastTerm.imag() > 0) == 0) {
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

void Fractal::ColorSmoothDarkRGB (int x, int y, Uint8* tabColors) {
	int iteration = matrix_iter[y * width + x];
	complex<double> lastTerm = matrix_lastTerm[y * width + x];
	double color = (iteration - log(log(abs(lastTerm) )))/max_iter;

	if (iteration == max_iter) {
		tabColors[0] = (Uint8) (0);
		tabColors[1] = (Uint8) (0);
		tabColors[2] = (Uint8) (0);
	}
	else {
		tabColors[0] = (Uint8) (255.0 * color);
		tabColors[1] = (Uint8) (255.0 * color);
		tabColors[2] = (Uint8) (255.0 * color);
	}
}

#include "App.h"

void App::Render()
{
	SDL_BlitSurface(fractal->matrix_color, NULL, surf_display, NULL);
	SDL_Flip(surf_display);
}

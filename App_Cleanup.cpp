#include "App.h"

void App::Cleanup()
{
    SDL_FreeSurface(surf_display);
	delete fractal;
    SDL_Quit();
}

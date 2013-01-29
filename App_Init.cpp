#include "App.h"

bool App::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;
	
	surf_display = SDL_SetVideoMode(width_display, height_display, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(surf_display == NULL)
		return false;

	//Load other ressources here
	
    return true;
}

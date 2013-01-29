#include "App.h"

void App::Cleanup()
{
    SDL_FreeSurface(surf_display);
	//Free other ressources here
    SDL_Quit();
}

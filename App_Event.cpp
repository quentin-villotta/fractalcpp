#include "App.h"

void App::Event(SDL_Event* event)
{
    if(event->type == SDL_QUIT)
        running = false;
	//See http://www.sdltutorials.com/sdl-events for more complex examples
}


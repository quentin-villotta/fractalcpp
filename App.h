#pragma once

#ifdef __GNUC__
#include <SDL/SDL.h>
#else
#include "SDL.h"
#endif

#include "Fractal.h"
#include "FractalMandelbrot.h"

class App
{
	private:
    	bool running;
		
    	SDL_Surface* surf_display;
		int width_display, height_display;
		
		Fractal* fractal;
		
	public:
    	App(int, int, int);
    	int Execute();

	public:
    	bool Init();
    	void Event(SDL_Event* Event);
    	void Loop();
    	void Render();
    	void Cleanup();	
};

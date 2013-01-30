/**
 * \class App
 *
 * \brief This class handles the main machinery of the application.
 *
 */
#pragma once

#ifdef __GNUC__
#include <SDL/SDL.h>
#else
#include "SDL.h"
#endif

#include "Fractal.h"
#include "FractalMandelbrot.h"
#include "FractalJulia.h"

class App
{
	private:
    	bool running;
		
		/// Screen surface
    	SDL_Surface* surf_display;
		
		/// Resolution of the window
		int width_display, height_display;
		
		/// Current view of the fractal
		Fractal* fractal;
		
	public:
    	App(int, int, int);
		
		/// Run the application
    	int Execute();

	public:
		/// Initialize SDL and load ressources
    	bool Init();
		
		/// What to do given an event from the user
    	void Event(SDL_Event* Event);
		
		/// Recalculate the fractal after an event (e.g. zooming)
    	void Loop();
		
		/// Display the fractal on the screen
    	void Render();
		
		/// Close SDL and free ressources
    	void Cleanup();	
};

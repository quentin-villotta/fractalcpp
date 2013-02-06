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

#include <boost/program_options.hpp>
	 
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
	 
#include "Fractal.h"
#include "FractalMandelbrot.h"
#include "FractalJulia.h"

#include "ColorBlackBlue.h"
#include "ColorBlackWhite.h"
#include "ColorBlackWhiteMod.h"
#include "ColorBlackWhiteSmooth.h"
#include "ColorTimeEscapeDarkRGB.h"

using namespace std;
 
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
		
		/// Last position of mouse click
		pair<int, int> last_mouse_click;
		
		/// Zoom scale
		double zoom_scale;
		
		// Color functions
		ColorBlackBlue color_black_blue;
		ColorBlackWhite color_black_white;
		ColorBlackWhiteMod color_black_white_mod;
		ColorBlackWhiteSmooth color_black_white_smooth;
		ColorTimeEscapeDarkRGB color_time_escape_dark_rgb;
		ColorFunction* color_functions[5];
		int id_cur_color;
		
		// Screenshots
		int id_cur_screenshot;
		string path_pictures;
		
	public:
    	App();
		
		/// Run the application
    	int Execute();

		/// Initialize SDL and load ressources
    	bool Init();
		
		/// What to do given an event from the user
    	void Event(SDL_Event* Event);
		
		/// Display the fractal on the screen
    	void Render();
		
		/// Close SDL and free ressources
    	void Cleanup();	
};

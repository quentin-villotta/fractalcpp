/**
 * \class SurfaceHelper
 *
 * \brief This class ...
 *
 */
#pragma once

#ifdef __GNUC__
#include <SDL/SDL.h>
#else
#include "SDL.h"
#endif

class SurfaceHelper
{
public:
	/// Constructor and destructor
	SurfaceHelper(void);
	~SurfaceHelper(void);
	
	/// Set color of a pixel in a SDL Surface
	static void PutPixelRGB(SDL_Surface*, int , int , Uint8, Uint8, Uint8);
};

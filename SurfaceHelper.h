#pragma once

#ifdef __GNUC__
#include <SDL/SDL.h>
#else
#include "SDL.h"
#endif

class SurfaceHelper
{
public:
	SurfaceHelper(void);
	~SurfaceHelper(void);
	
	static void PutPixelRGB(SDL_Surface*, int , int , Uint8, Uint8, Uint8);
};

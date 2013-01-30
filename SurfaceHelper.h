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
	
	static PutPixelRGB(SDL_Surface* surf, int x, int y, Uint8 r, Uint8 g, Uint8 b)
	{
		Uint32* pixels = (Uint32 *)surf->pixels;
		Unint32 pixel = SDL_MapRGB(surf->format, r, g, b); 
		pixels[y * surf->w + x] = pixel;
	}
};

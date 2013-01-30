#include "SurfaceHelper.h"

void SurfaceHelper::PutPixelRGB(SDL_Surface* surf, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
	Uint32* pixels = (Uint32 *)surf->pixels;
	Uint32 pixel = SDL_MapRGB(surf->format, r, g, b); 
	pixels[y * surf->w + x] = pixel;
}

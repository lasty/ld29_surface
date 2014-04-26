
#include "sdl/surface.h"

#include "sdl/sdl_exception.h"


Surface::Surface()
{

}

Surface::Surface(int width, int height)
: width(width)
, height(height)
{
	Uint32 rmask, gmask, bmask, amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);

	if (surface == nullptr)
	{
		throw SDLException("SDL_CreateRGBSurface");
	}
}


Surface::~Surface()
{
	if (surface)
	{
		SDL_FreeSurface(surface);
	}
}


Surface::Surface(Surface &&move)
{
	std::swap(surface, move.surface);
	std::swap(width, move.width);
	std::swap(height, move.height);
}


Surface& Surface::operator=(Surface &&moveassign)
{
	std::swap(surface, moveassign.surface);
	std::swap(width, moveassign.width);
	std::swap(height, moveassign.height);

	return *this;
}


void Surface::Lock()
{
	if (SDL_MUSTLOCK(surface))
	{
		int ret = SDL_LockSurface(surface);
		if (ret < 0)
		{
			throw SDLException("SDL_LockSurface");
		}
	}
}


void Surface::Unlock()
{
	if (SDL_MUSTLOCK(surface))
	{
		SDL_UnlockSurface(surface);
	}
}


void Surface::SetPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	if (x<0 or y<0 or x>=width or y>=height)
	{
		throw std::logic_error("SetPixel position out of range");
	}

	Uint8* pixels = (Uint8*)(surface->pixels);

	pixels += (surface->pitch * y) + (sizeof(Uint32) * x);

	pixels[0] = r;
	pixels[1] = g;
	pixels[2] = b;
	pixels[3] = a;
}



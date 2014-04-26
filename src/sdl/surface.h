#ifndef SDL_SURFACE_H
#define SDL_SURFACE_H


#include "sdl/sdl_headers.h"


class Surface
{
public:
	Surface();
	Surface(int width, int height);
	~Surface();

	Surface(const Surface &copy) = delete;
	Surface(Surface &&move);

	Surface& operator=(const Surface &copyassign) = delete;
	Surface& operator=(Surface &&moveassign);

private:
	SDL_Surface *surface = nullptr;
	int width = 0;
	int height = 0;

public:
	SDL_Surface* GetSurface() const { return surface; }

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }


	void Lock();
	void Unlock();

	void SetPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

};


#endif // SDL_SURFACE_H

#ifndef SDL_SDL_INIT_H
#define SDL_SDL_INIT_H


#include "sdl/sdl_headers.h"


class SDL2
{
public:
	SDL2();
	~SDL2();

	SDL2(const SDL2 &copy) = delete;
	SDL2(SDL2 &&move) = delete;
};


#endif // SDL_SDL_INIT_H

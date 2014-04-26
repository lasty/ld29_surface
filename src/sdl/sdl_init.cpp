
#include "sdl/sdl_init.h"

#include "sdl/sdl_exception.h"


SDL2::SDL2()
{
	int ret = SDL_Init(SDL_INIT_VIDEO);

	if (ret < 0)
	{
		throw SDLException("SDL_Init()");
	}


}

SDL2::~SDL2()
{
	SDL_Quit();
}


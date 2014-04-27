
#include "sdl/sdl_init.h"

#include "sdl/sdl_exception.h"


SDL2::SDL2()
{
	int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	if (ret < 0)
	{
		throw SDLException("SDL_Init()");
	}


	/*
	//Not sure if this is needed for just playing .WAV files

	int flags = MIX_INIT_OGG;
	int mixinit = Mix_Init(flags);

	if ((mixinit & flags) != flags)
	{
		throw SDLException("Mix_Init");
	}
	*/


	const int freq = 22050;//44100;
	const auto format = MIX_DEFAULT_FORMAT; //AUDIO_S16;
	const int channels = 2;
	const int chunksize = 2048;//4096;
	int mixret = Mix_OpenAudio(freq, format, channels, chunksize);

	if (mixret == -1 )
	{
		throw SDLException("Mix_OpenAudio");
	}
}

SDL2::~SDL2()
{
	Mix_CloseAudio();

	SDL_Quit();
}


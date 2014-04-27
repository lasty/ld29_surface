
#include "sdl/sound.h"

#include "sdl/sdl_exception.h"


Sound::Sound()
{

}


Sound::Sound(const std::string filename)
{
	chunk = Mix_LoadWAV(filename.c_str());

	if (chunk == nullptr)
	{
		throw SDLException("Mix_LoadWAV");
	}
}

Sound::~Sound()
{
	if (chunk)
	{
		Mix_HaltChannel(-1);  //< this is probably overkill; halts all channels
		Mix_FreeChunk(chunk);
	}
}

Sound::Sound(Sound &&move)
{
	std::swap(chunk, move.chunk);
}

Sound& Sound::operator=(Sound &&moveassign)
{
	std::swap(chunk, moveassign.chunk);

	return *this;
}


void Sound::Play()
{
	if (not chunk) throw std::logic_error("Sound::Play(): Playing uninitialized sound");

	int chan = Mix_PlayChannel(-1, chunk, 0);

	if (chan == -1)
	{
		//XXX this fails when not enough channels are available, except there is no code to check
		//throw SDLException("Mix_PlayChannel");
	}
}

int Sound::PlayLoop()
{
	if (not chunk) throw std::logic_error("Sound::PlayLoop(): Playing uninitialized sound");

	int chan = Mix_PlayChannel(-1, chunk, -1);

	if (chan == -1)
	{
		//XXX this fails when not enough channels are available, except there is no code to check
		//throw SDLException("Mix_PlayChannel");
	}

	return chan;
}

void Sound::StopLoop(int chan)
{
	Mix_HaltChannel(chan);
}



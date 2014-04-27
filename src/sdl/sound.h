#ifndef SDL_SOUND_H
#define SDL_SOUND_H

//wrapper around Mix_Chunk
#include "sdl/sdl_headers.h"

#include <string>

class Sound
{
public:
	Sound();
	Sound(const std::string filename);

	~Sound();
	Sound(const Sound& copy) = delete;
	Sound(Sound &&move);
	Sound& operator=(const Sound& copyassign) = delete;
	Sound& operator=(Sound &&moveassign);

private:
	Mix_Chunk *chunk = nullptr;

public:

	Mix_Chunk* GetChunk() const { return chunk; }

	void Play();

	int PlayLoop();

	void StopLoop(int);

};


#endif // SDL_SOUND_H

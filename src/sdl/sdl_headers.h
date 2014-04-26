#ifndef SDL_SDL_HEADERS_H
#define SDL_SDL_HEADERS_H

#ifdef __APPLE__

//Apple uses the framework prefix
#include <SDL2/SDL.h>

#else

#include <SDL.h>

#ifdef __WIN32__
//Windows SDL redefines main which screws things up
#undef main
#endif

#endif

#endif // SDL_SDL_HEADERS_H

#ifndef SDL_SDL_HEADERS_H
#define SDL_SDL_HEADERS_H

#ifdef __APPLE__

//Apple uses the framework prefix
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#else

#include <SDL.h>
#include <SDL_image.h>

#ifdef __WIN32__
//Windows SDL redefines main which screws things up
#undef main
#endif

#endif

#endif // SDL_SDL_HEADERS_H

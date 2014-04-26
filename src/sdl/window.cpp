
#include "sdl/window.h"

#include "sdl/sdl_exception.h"

Window::Window(const std::string &title, int width, int height, int exflags)
{
	Uint32 flags = SDL_WINDOW_OPENGL | exflags;

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, 50,
		width, height, flags);

	if (window == nullptr)
	{
		throw SDLException("SDL_CreateWindow");
	}
}


Window::~Window()
{
	SDL_DestroyWindow(window);
}



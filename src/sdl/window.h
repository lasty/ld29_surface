#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H


#include "sdl/sdl_init.h"

#include <string>

class Window
{
public:
	Window(const std::string &title, int width, int height, int exflags = 0);
	~Window();

	Window(const Window &copy) = delete;
	Window(Window &&move) = delete;

private:
	SDL_Window *window = nullptr;

	int width = 0;
	int height = 0;

public:
	SDL_Window* GetWindow() const { return window; }

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
};


#endif // SDL_WINDOW_H

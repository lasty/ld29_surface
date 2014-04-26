
#include "sdl/sdl_init.h"
#include "sdl/window.h"

#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "Hello world," << std::endl;

	SDL2 init;
	Window window("BeneathTheSurface", 800, 480);

	SDL_Delay(1000);

	std::cout << "but beneath the surface" << std::endl;
}

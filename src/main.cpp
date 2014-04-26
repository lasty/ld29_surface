
#include "sdl/sdl_init.h"
#include "sdl/window.h"
#include "sdl/renderer.h"

#include "sdl/surface.h"
#include "sdl/texture.h"

#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "Hello world," << std::endl;

	SDL2 init;
	Window window("BeneathTheSurface", 800, 480);
	Renderer rend(window);

	//test move semantics
	{
		Surface s1;
		Surface s2(128, 128);

		s1 = std::move(s2);

		Texture t1;
		Texture t2(rend, s1);
		Texture t3(rend, 128, 128);

		t1 = std::move(t2);
	}

	rend.SetColour(20, 30, 40, 255);
	rend.Clear();
	rend.Flip();
	SDL_Delay(1000);


	std::cout << "but beneath the surface" << std::endl;
}

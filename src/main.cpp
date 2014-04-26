
#include "sdl/sdl_init.h"
#include "sdl/window.h"
#include "sdl/renderer.h"

#include "sdl/surface.h"
#include "sdl/texture.h"

#include "font/font.h"

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

	Font f1("data/fonts/DroidSans.ttf", 48);

	for(char ch : "Beneath the Surface")
	{
		rend.SetColour(20, 30, 40, 255);
		rend.Clear();


		Glyph& g1 = f1.GetGlyph(ch);

		if (not g1.blank)
		{
			Texture tg1{rend, g1.GetSurface() };

			rend.Copy(tg1, nullptr, nullptr);
		}

		rend.Flip();
		SDL_Delay(200);
	}


	std::cout << "but beneath the surface" << std::endl;
}

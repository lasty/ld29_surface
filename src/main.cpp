
#include "sdl/sdl_init.h"
#include "sdl/window.h"
#include "sdl/renderer.h"

#include "sdl/surface.h"
#include "sdl/texture.h"

#include "font/font.h"
#include "font/text.h"

#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "Hello world," << std::endl;

	SDL2 init;
	Window window("BeneathTheSurface", 800, 480);
	Renderer rend(window);


	Font f1("data/fonts/DroidSans.ttf", 48);

	Text text1(rend, f1, "Release the Kraken");

	rend.SetColour(20, 30, 40, 255);
	rend.Clear();

	text1.Render(rend, 100, 100);

	rend.Flip();
	SDL_Delay(1200);

	for(char ch : "Beneath the Surface")
	{
		rend.SetColour(20, 30, 40, 255);
		rend.Clear();


		Glyph& g1 = f1.GetGlyph(ch);

		if (not g1.blank)
		{
			Texture tg1{rend, g1.GetSurface() };
			tg1.SetBlend();

			rend.Copy(tg1, nullptr, nullptr);
		}

		//Texture tgf1{rend, text1.GetSurface() };

		//SDL_Rect p = text1.Place(100,100);
		//rend.Copy(text1.GetTexture(), nullptr, nullptr);

		rend.Flip();
		SDL_Delay(200);
	}


	std::cout << "but beneath the surface" << std::endl;
}

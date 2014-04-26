

#include "sdl/surface.h"
#include "sdl/texture.h"

#include "font/font.h"
#include "font/text.h"

#include "game_base.h"

#include <iostream>


class TestGame : public Game_Base
{
public:
	TestGame(const std::string &title, int w, int h)
	: Game_Base(title, w, h)
	{

	}

	Font f1{"data/fonts/DroidSans.ttf", 48};

	Text text1{renderer, f1, "Under the Surface"};

	bool dragging = false;
	int textx=100;
	int texty=100;

	void Render(Renderer &rend) override
	{
		rend.SetColour(20, 30, 40, 255);
		rend.Clear();

		text1.Render(rend, textx, texty);
	}

	void OnKey(SDL_KeyboardEvent &e, bool down) override
	{
		if (e.keysym.sym == SDLK_q or e.keysym.sym==SDLK_ESCAPE) Quit();
	}

	void OnMouseButton(int x, int y, int but, bool down) override
	{
		if (but == 1 and down)
		{
			dragging = true;
			textx=x;
			texty=y;
		}
		if (but == 1 and not down)
		{
			dragging = false;
		}
	}

	void OnMouseMove(int x, int y) override
	{
		if (dragging)
		{
			textx=x;
			texty=y;
		}
	}

	void OnFPS(int frames) override
	{
		std::cout << "FPS: " << frames << std::endl;
	}
};



int main(int argc, char* argv[])
{
	std::cout << "Hello world," << std::endl;

	TestGame test("BeneathTheSurface", 800, 480);

	test.Run();


	std::cout << "but beneath the surface" << std::endl;
}

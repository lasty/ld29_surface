

#include "sdl/surface.h"
#include "sdl/texture.h"

#include "font/font.h"
#include "font/text.h"

#include "tiles/tile.h"

#include "tiles/map.h"

#include "sprites/sprite.h"

#include "game_base.h"

#include <iostream>
#include <sstream>

class TestGame : public Game_Base
{
public:
	TestGame(const std::string &title, int w, int h)
	: Game_Base(title, w, h)
	{
		Tile t_grass{tiles, 32, 0, 0, 1, 1, 2};
		Tile t_sand{tiles, 32, 1, 0, 1, 1, 2};

		worldmap.NewTileDef("grass", std::move(t_grass));
		worldmap.NewTileDef("sand", std::move(t_sand));

		worldmap.NewMap(10, 10, 64, "grass");

		for (int i=0; i<10; i++)
		{
			worldmap.SetTile(i, 2, "sand");
		}
	}

	Font f1{"data/fonts/DroidSans.ttf", 48};
	Font smallfont{"data/fonts/DroidSans.ttf", 16};

	Text text1{renderer, f1, "Under the Surface"};

	Text fps_text{renderer, smallfont, "-"};

	Texture tiles{renderer, "data/tiles.png"};

	Texture sprites{renderer, "data/sprites.png"};

	Sprite s_gold{sprites, 32, 0, 0, 1, 1, 2};

	Map worldmap;

	bool dragging = false;
	int textx=100;
	int texty=100;

	bool dragging2 = false;
	int gx = 0;
	int gy = 0;


	void Render(Renderer &rend) override
	{
		rend.SetColour(20, 30, 40, 255);
		rend.Clear();

		worldmap.Render(rend, 0, 0);

		s_gold.Render(rend, gx, gy, 0.0f, 1.0f);

		text1.Render(rend, textx, texty);
		fps_text.Render(rend, -10, 5);
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

		if (but == 3)
		{
			dragging2 = down;
			gx=x;
			gy=y;
		}
	}

	void OnMouseMove(int x, int y) override
	{
		if (dragging)
		{
			textx=x;
			texty=y;
		}

		if (dragging2)
		{
			gx = x;
			gy = y;
		}
	}

	void OnFPS(int frames) override
	{
		std::ostringstream s;
		s << "FPS: " << frames;

		fps_text.SetText(renderer, smallfont, s.str());
	}
};



int main(int argc, char* argv[])
{
	std::cout << "Hello world," << std::endl;

	TestGame test("BeneathTheSurface", 800, 480);

	test.Run();


	std::cout << "but beneath the surface" << std::endl;
}

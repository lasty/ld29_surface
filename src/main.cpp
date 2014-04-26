

#include "sdl/surface.h"
#include "sdl/texture.h"

#include "font/font.h"
#include "font/text.h"

#include "tiles/tile.h"

#include "tiles/map.h"

#include "sprites/sprite.h"

#include "game_base.h"

#include <glm/glm.hpp>

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

	bool dragging1 = false;
	bool dragging2 = false;
	bool dragging3 = false;

	int textx=100;
	int texty=100;

	int gx = 100;
	int gy = 100;

	float guyx = 100;
	float guyy = 100;
	float guyanim = 0.0f;

	bool guywalking = false;
	bool guywalkdir = false;
	float setguyx = 100;
	float setguyy = 100;

	Sprite s_guyidle1{sprites, 64, 0, 2, 1, 1, 1, 32, 58};
	Sprite s_guyidle2{sprites, 64, 1, 2, 1, 1, 1, 32, 58};

	Sprite s_guywalk1{sprites, 64, 0, 3, 1, 1, 1, 32, 58};
	Sprite s_guywalk2{sprites, 64, 1, 3, 1, 1, 1, 32, 58};

	void RenderGuy(Renderer &rend)
	{
		Sprite *s = nullptr;
		if (guywalking)
		{
			if (guyanim < 0.2f)
			{
				s = &s_guywalk1;
			}
			else
			{
				s = &s_guywalk2;
			}
			if (guyanim >= 0.4f) guyanim = 0.0f;
		}
		else
		{
			if (guyanim < 0.5f)
			{
				s = &s_guyidle1;
			}
			else
			{
				s = &s_guyidle2;
			}
		}

		SDL_RendererFlip flip = guywalkdir ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

		s->Render(renderer, guyx, guyy, 0.0f, 1.0f, flip);
	}

	void UpdateGuy(float dt)
	{
		const float speed = 200.0f;
		guyanim += dt;
		if (guyanim > 1.0f) guyanim -= 1.0f;


		glm::vec2 guy{guyx, guyy};

		glm::vec2 dest{setguyx, setguyy};

		float distance = glm::distance(guy, dest);

		if (distance < 1.0f)
		{
			guywalking = false;
			return;
		}

		if (abs(guyx - setguyx) >= 1.0f)
		{
			guywalkdir = (guyx < setguyx);
		}

		glm::vec2 dir = glm::normalize(dest - guy);

		guy += dir *  (dt * speed);

		guyx = guy.x;
		guyy = guy.y;

	}

	void Update(float dt) override
	{
		UpdateGuy(dt);
	}


	void Render(Renderer &rend) override
	{
		rend.SetColour(20, 30, 40, 255);
		rend.Clear();

		worldmap.Render(rend, 0, 0);

		s_gold.Render(rend, gx, gy, 0.0f, 1.0f);

		RenderGuy(rend);
		text1.Render(rend, textx, texty);
		fps_text.Render(rend, -10, 5);
	}

	void OnKey(SDL_KeyboardEvent &e, bool down) override
	{
		if (e.keysym.sym == SDLK_q or e.keysym.sym==SDLK_ESCAPE) Quit();
	}

	void OnMouseButton(int x, int y, int but, bool down) override
	{
		if (but == 1)
		{
			dragging1 = down;
			setguyx = x;
			setguyy = y;
			guywalking=true;
		}
		if (but == 2)
		{
			dragging2 = down;
			textx=x;
			texty=y;
		}

		if (but == 3)
		{
			dragging3 = down;
			gx=x;
			gy=y;
		}
	}

	void OnMouseMove(int x, int y) override
	{
		if (dragging1)
		{
			setguyx = x;
			setguyy = y;
			guywalking=true;
		}

		if (dragging2)
		{
			textx=x;
			texty=y;
		}

		if (dragging3)
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



#include "sdl/surface.h"
#include "sdl/texture.h"
#include "sdl/sound.h"

#include "font/font.h"
#include "font/text.h"


#include "sprites/sprite.h"
#include "sprites/circle.h"
#include "sprites/animated_sprite.h"

#include "world.h"

#include "object.h"

#include "game_base.h"

#include <glm/glm.hpp>

#include <iostream>
using std::cout;
using std::endl;

#include <sstream>
#include <memory>

class AnimatedGuy : public AnimatedSprite
{
private:
	Texture sprites;

public:
	AnimatedGuy(Renderer &renderer)
	: sprites{renderer, "data/sprites.png"}
	{
		AddFrame("idle", Sprite{sprites, 64, 0, 2, 1, 1, 1, 32, 58}, 0.5f);
		AddFrame("idle", Sprite{sprites, 64, 1, 2, 1, 1, 1, 32, 58}, 0.6f);

		AddFrame("walk", {sprites, 64, 0, 3, 1, 1, 1, 32, 58}, 0.2f);
		AddFrame("walk", {sprites, 64, 1, 3, 1, 1, 1, 32, 58}, 0.2f);
	}
};


class SpriteList
{
private:
	std::map<std::string, Sprite> list;

	Texture texture;

public:
	SpriteList(Renderer &rend)
	: texture(rend, "data/sprites.png")
	{
		list.emplace( std::make_pair("gold", Sprite{texture, 32, 0, 0, 1, 1, 2}) );
	}

	Sprite &GetSprite(const std::string s)
	{
		return (list.at(s));
	}
};


class GoldObject : public Object
{
public:
	GoldObject(int x, int y, Sprite &s)
	:Object(glm::vec3{x, y, 0}, 16.0, s)
	{
		//cout << "Making gold!" << endl;
	}

	~GoldObject()
	{
		//cout << "Deleting gold" << endl;
	}
};


class TestGame;

class GuyObject : public Object
{
public:
	GuyObject(TestGame *tg, AnimatedSprite &anim)
	: Object ( glm::vec3{0.0f, 0.0f, 0.0f}, 16.0f, anim, "idle" )
	, tg(tg)
	{

	}

	TestGame *tg = nullptr;

	void Collide(Object &o) override;

};



class TestGame : public Game_Base
{
public:
	TestGame(const std::string &title, int w, int h)
	: Game_Base(title, w, h)
	{

		NewNugget();
		UpdateScore();

		InitGuy();
	}

	~TestGame()
	{
	}

	Font f1{"data/fonts/DroidSans.ttf", 48};
	Font smallfont{"data/fonts/DroidSans.ttf", 16};

	Text text1{renderer, f1, "Under the Surface"};

	Text fps_text{renderer, smallfont, "-"};

	Text gold_score_text{renderer, smallfont, ""};

	Texture tiles{renderer, "data/tiles.png"};


	World world {renderer};

	bool draw_radii = true;

	bool dragging1 = false;
	bool dragging2 = false;
	bool dragging3 = false;

	int textx=100;
	int texty=10;

	int gx = 100;
	int gy = 100;

	float guywalkdist = 0.0f;

	bool guywalking = false;
	float setguyx = 100;
	float setguyy = 100;

	AnimatedGuy guy_animsprite { renderer };

	GuyObject Guy{ this, guy_animsprite };

	Circle circle1{1.0f, 16, false};
	Circle circle2{1.0f, 16, true};


	Sound sound1{"data/sounds/beep1.wav"};
	Sound sound_walk1{"data/sounds/walk_grass1.wav"};
	Sound sound_walk2{"data/sounds/walk_sand1.wav"};

	void InitGuy()
	{
		guywalking = true;
		Guy.PlayAnimation("idle");
	}

	void PlaySound()
	{
		sound1.Play(); //Mix_PlayChannel(-1, sound1, 0);
	}

	void GuyStepSound()
	{
		sound_walk2.Play();
	}

	SpriteList sprite_list{renderer};

	int gold_nuggets = 0;

	void RenderGuy(Renderer &rend)
	{
		if (draw_radii)
		{
			circle2.Render(renderer, Guy);
		}

		Guy.Render(rend);
//		s.Render(renderer, guyx, guyy, 0.0f, 1.0f, flip);
	}

	void UpdateScore()
	{
		std::ostringstream msg;
		msg << "Gold: " << gold_nuggets;

		gold_score_text.SetText(renderer, smallfont, msg.str());
	}

	void NewNugget(int num = 10)
	{
		for (int i=0; i<num; ++i)
		{
			int gx = rand() % 500 + 100;
			int gy = rand() % 300 + 100;

			Sprite &gspr = sprite_list.GetSprite("gold");
			Object * nug = new GoldObject(gx, gy, gspr);

			world.AddObject(nug);
		}
	}

	void GotNugget(Object &o)
	{
		o.MarkForDeletion(true);

		gold_nuggets++;
		PlaySound();
		UpdateScore();
		NewNugget(1);
	}


	void CheckCollision()
	{
/*
		glm::vec2 nugget_pos{gx, gy};
		glm::vec2 player_pos = Guy.GetPosition2();

		float player_radius = Guy.GetRadius();

		float dist = glm::distance(player_pos, nugget_pos);

		dist -= nugget_radius;
		dist -= player_radius;

		if (dist < 0)
		{
		}

*/

	}

	void UpdateGuy(float dt)
	{
		const float speed = 200.0f;

		Guy.Update(dt);

		if (guywalking)
		{
			guywalkdist+=dt;
			if (guywalkdist >= 0.2f)
			{
				GuyStepSound();
				guywalkdist = 0.0f;
			}
		}


		glm::vec2 guy = Guy.GetPosition2();

		glm::vec2 dest{setguyx, setguyy};

		float distance = glm::distance(guy, dest);

		if (distance < 1.0f)
		{
			if (guywalking)
			{
				Guy.PlayAnimation("idle");
				GuyStepSound();
			}
			guywalking = false;
			return;
		}

		if (distance >= 1.0f)
		{
			Guy.SetFlip(not (guy.x < setguyx));
		}

		glm::vec2 dir = glm::normalize(dest - guy);

		guy += dir *  (dt * speed);

		Guy.SetPosition2(guy);

	}

	void Update(float dt) override
	{
		world.CheckForCollisionsFrom(Guy);

		world.Update(dt);

		UpdateGuy(dt);

		CheckCollision();
	}


	void Render(Renderer &rend) override
	{
		rend.SetColour(20, 30, 40, 255);
		rend.Clear();

		world.Render(rend);

		if (draw_radii)
		{
			circle1.SetColour(244, 199, 17, 128);
//			circle1.Render(rend, gx, gy, 16);
		}

		RenderGuy(rend);
		text1.Render(rend, textx, texty);
		fps_text.Render(rend, -10, 5);

		gold_score_text.Render(rend, 10, -5);
	}

	void OnKey(SDL_KeyboardEvent &e, bool down) override
	{
		if (e.keysym.sym == SDLK_q or e.keysym.sym==SDLK_ESCAPE) Quit();

		else if (e.keysym.sym == SDLK_r and down) { draw_radii = not draw_radii; }

		else if (e.keysym.sym == SDLK_g and down) { NewNugget(); }
	}

	void OnMouseButton(int x, int y, int but, bool down) override
	{
		if (but == 1)
		{
			dragging1 = down;
			setguyx = x;
			setguyy = y;
			if (not guywalking) { GuyStepSound(); }
			guywalking=true;
			Guy.PlayAnimation("walk");
		}
		if (but == 2)
		{
			dragging2 = down;
			textx=x;
			texty=y;
		}

/*		if (but == 3)
		{
			dragging3 = down;
			gx=x;
			gy=y;
		}
*/
	}

	void OnMouseMove(int x, int y) override
	{
		if (dragging1)
		{
			setguyx = x;
			setguyy = y;
			if (not guywalking) { GuyStepSound(); }
			guywalking=true;
		}

		if (dragging2)
		{
			textx=x;
			texty=y;
		}

/*
		if (dragging3)
		{
			gx = x;
			gy = y;
		}
*/
	}

	void OnFPS(int frames) override
	{
		std::ostringstream s;
		s << "FPS: " << frames;

		fps_text.SetText(renderer, smallfont, s.str());
	}
};


void GuyObject::Collide(Object &o)
{
	tg->GotNugget(o);
}



int main(int argc, char* argv[])
{
	std::cout << "Hello world," << std::endl;

	TestGame test("BeneathTheSurface", 800, 480);

	test.Run();


	std::cout << "but beneath the surface" << std::endl;
}

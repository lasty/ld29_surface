
#include "game_base.h"


Game_Base::Game_Base(const std::string &title, int width, int height)
: window(title, width, height)
, renderer(window)
{

}

Game_Base::~Game_Base()
{
}

void Game_Base::Run()
{
	last_time = SDL_GetTicks();
	running = true;

	while (running)
	{
		ProcessEvents();

		float delta_time = UpdateTimers();
		Update(delta_time);

		UpdateFPS(delta_time);

		Render(renderer);

		renderer.Flip();
	}
}


void Game_Base::ProcessEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			Quit();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			OnKey(event.key, true);
		}
		else if (event.type == SDL_KEYUP)
		{
			OnKey(event.key, false);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			int x = event.button.x;
			int y = event.button.y;
			int but = event.button.button;
			OnMouseButton(x, y, but, true);
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			int x = event.button.x;
			int y = event.button.y;
			int but = event.button.button;
			OnMouseButton(x, y, but, false);
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			int x = event.button.x;
			int y = event.button.y;
			OnMouseMove(x, y);
		}


	}
}


float Game_Base::UpdateTimers()
{
	long this_time = SDL_GetTicks();
	float delta_time = float(this_time - last_time) / 1000.0f;
	last_time = this_time;

	return delta_time;
}


void Game_Base::UpdateFPS(float dt)
{
	fps_framecount++;
	fps_frametime += dt;

	if (fps_frametime >= 1.0f)
	{
		OnFPS(fps_framecount);
		fps_framecount = 0;

		fps_frametime -= 1.0f;
	}
}


void Game_Base::OnFPS(int frames)
{
}

void Game_Base::Update(float dt)
{

}


void Game_Base::Render(Renderer &rend)
{
	rend.Clear();
}


void Game_Base::Quit()
{
	running = false;
}


void Game_Base::OnKey(SDL_KeyboardEvent &e, bool down)
{
}


void Game_Base::OnMouseButton(int x, int y, int but, bool down)
{
}


void Game_Base::OnMouseMove(int x, int y)
{
}





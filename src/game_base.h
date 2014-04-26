#ifndef GAME_BASE_H
#define GAME_BASE_H


#include "sdl/sdl_headers.h"

#include "sdl/renderer.h"


class Game_Base
{
public:
	Game_Base(const std::string &title, int width, int height);
	virtual ~Game_Base();

private:
	SDL2 init;
	Window window;
protected:
	Renderer renderer;

	long last_time = 0;
	int fps_framecount = 0;
	float fps_frametime = 0.0f;

	bool running = false;

public:
	Window& GetWindow() { return window; }
	Renderer& GetRenderer() { return renderer; }
	int GetWidth() const { return renderer.GetWidth(); }
	int GetHeight() const { return renderer.GetHeight(); }

	void Run();

private:
	void ProcessEvents();
	float UpdateTimers();
	void UpdateFPS(float delta_time);

public:

	virtual void OnFPS(int frames);
	virtual void Update(float dt);
	virtual void Render(Renderer &rend);

	void Quit();

	virtual void OnKey(SDL_KeyboardEvent &e, bool down);

	virtual void OnMouseButton(int x, int y, int but, bool down);
	virtual void OnMouseMove(int x, int y);

};


#endif //  GAME_BASE_H

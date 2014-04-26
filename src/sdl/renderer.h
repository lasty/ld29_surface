#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H


#include "sdl/window.h"

class Texture;

class Renderer
{
public:
	Renderer(Window &window, int exflags = 0);
	~Renderer();

	Renderer(const Renderer &copy) = delete;
	Renderer(Renderer &&move) = delete;

private:
	SDL_Renderer *renderer = nullptr;
	Window &window;

public:
	SDL_Renderer* GetRenderer() const { return renderer; }

	void SetColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
	void Clear() const;
	void Copy(const Texture &texture, const SDL_Rect *src, const SDL_Rect *dest);
	void Flip() const;

	int GetWidth() const { return window.GetWidth(); }
	int GetHeight() const { return window.GetHeight(); }

};


#endif // SDL_RENDERER_H

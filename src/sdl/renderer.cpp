
#include "sdl/renderer.h"

#include "sdl/sdl_exception.h"

#include "sdl/texture.h"

Renderer::Renderer(Window &window, int exflags)
: window(window)
{
	Uint32 flags = SDL_RENDERER_ACCELERATED;
	//flags |= SDL_RENDERER_PRESENTVSYNC;
	flags |= exflags;

	renderer = SDL_CreateRenderer(window.GetWindow(), -1, flags);

	if (renderer == nullptr)
	{
		throw SDLException("SDL_CreateRenderer");
	}
}


Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}


void Renderer::SetColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::Clear() const
{
	SDL_RenderClear(renderer);
}

void Renderer::Copy(const Texture &texture, const SDL_Rect *src, const SDL_Rect *dest)
{
	SDL_RenderCopy(renderer, texture.GetTexture(), src, dest);
}

void Renderer::CopyEx(const Texture &texture, const SDL_Rect *src, const SDL_Rect *dest
		, double angle, const SDL_Point* center, const SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, texture.GetTexture(), src, dest, angle, center, flip);
}

void Renderer::Flip() const
{
	SDL_RenderPresent(renderer);
}


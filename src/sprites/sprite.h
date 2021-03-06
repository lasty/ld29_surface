#ifndef SPRITES_SPRITE_H
#define SPRITES_SPRITE_H

#include "sdl/texture.h"
#include "sdl/renderer.h"

class Sprite
{
public:

	Sprite(Texture &texture, int tilesize, int x, int y, int xspan=1, int yspan=1, int zoom=2);
	Sprite(Texture &texture, int tilesize, int x, int y, int xspan, int yspan, int zoom, int centerx, int centery);

	Texture *texture_ref = nullptr;

	SDL_Rect src;
	SDL_Rect dest;

	int centerx = 0;
	int centery = 0;

	void Render(Renderer &rend, float x, float y, float rot, float zoom, SDL_RendererFlip flip = SDL_FLIP_NONE);
};


#endif // SPRITES_SPRITE_H

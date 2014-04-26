
#include "sprites/sprite.h"


Sprite::Sprite(Texture &texture, int tilesize, int x, int y, int xspan, int yspan, int zoom)
: texture_ref(&texture)
{
	src.x = x*tilesize;
	src.y = y*tilesize;

	src.w = xspan * tilesize;
	src.h = yspan * tilesize;

	dest.x=0;
	dest.y=0;
	dest.w = src.w * zoom;
	dest.h = src.h * zoom;

	centerx = dest.w / 2.0f;
	centery = dest.h / 2.0f;

}

Sprite::Sprite(Texture &texture, int tilesize, int x, int y, int xspan, int yspan, int zoom, int centerx, int centery)
: Sprite(texture, tilesize, x, y, xspan, yspan, zoom)
{
	this->centerx = centerx * zoom;
	this->centery = centery * zoom;
}

void Sprite::Render(Renderer &rend, float x, float y, float rot, float zoom, SDL_RendererFlip flip)
{
	dest.x = x - centerx;
	dest.y = y - centery;

	rend.CopyEx(*texture_ref, &src, &dest, rot, nullptr, flip);
}


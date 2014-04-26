#ifndef TILES_TILE_H
#define TILES_TILE_H

#include "sdl/sdl_headers.h"
#include "sdl/texture.h"

class Tile
{
public:
	Tile(Texture &texture, int gridsize, int x, int y, int xspan=1, int yspan=1, int zoom=2);

	Texture *tex_ref;

	SDL_Rect src;
	SDL_Rect dest;

	void Render(Renderer &rend, int x, int y);
};


#endif // TILES_TILE_H

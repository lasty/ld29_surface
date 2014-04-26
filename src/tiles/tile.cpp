
#include "tiles/tile.h"


Tile::Tile(Texture &texture, int grids, int x, int y, int xspan, int yspan, int zoom)
: tex_ref(&texture)
{
	int width = texture.GetWidth();
	int tilesize = width / grids;

	src.x = x*tilesize;
	src.y = y*tilesize;

	src.w = xspan * tilesize;
	src.h = yspan * tilesize;

	dest.x=0;
	dest.y=0;
	dest.w = src.w * zoom;
	dest.h = src.h * zoom;
}


void Tile::Render(Renderer &rend, int x, int y)
{
	dest.x = x;
	dest.y = y;
	rend.Copy(*tex_ref, &src, &dest);
}




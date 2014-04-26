
#include "tiles/map.h"

#include "tiles/tile.h"
#include "sdl/renderer.h"

Cell::Cell(Map *map, Tile &tile, int worldx, int worldy)
: map(map)
, tile(&tile)
, worldx(worldx)
, worldy(worldy)
{

}


void Cell::Render(Renderer &rend)
{
	tile->Render(rend, worldx, worldy);
}


Map::Map()
{

}


void Map::NewTileDef(const std::string &name, Tile &&tile)
{
	tile_defs.emplace( make_pair(name, std::move(tile)) );
}

Tile & Map::GetTileDef(const std::string &def)
{
	auto it = tile_defs.find(def);
	if (it == tile_defs.end()) throw std::logic_error("Coudnt find tile def");

	return it->second;
}

void Map::SetTile(int x, int y, const std::string &tilename)
{
	if (x<0 or x>=world_width) throw std::logic_error("SetTile: x value out of range");
	if (y<0 or y>=world_height) throw std::logic_error("SetTile: y value out of range");

	Tile & tile = GetTileDef(tilename);

	GetCell(x, y) = Cell(this, tile, x*tile_size, y*tile_size);
}


void Map::NewMap(int width, int height, int tilesize, const std::string &blank)
{
	world_width=width;
	world_height=height;
	this->tile_size = tilesize;

	world.clear();

	Tile & defaulttile = GetTileDef(blank);

	for(int y = 0; y < height; y++)
	{
		world.emplace_back( Row{} );
		auto &row = world.back();
		for( int x=0; x < width; x++)
		{
			row.emplace_back( Cell(this, defaulttile, x*tile_size, y*tile_size) );
		}

		if (int(row.size()) != width) throw std::logic_error("Row size mismatch");
	}
	if (int(world.size()) != height) throw std::logic_error("Column size mismatch");
}


void Map::Render(Renderer &render, int xoffset, int yoffset)
{
	for( auto &row : world)
	{
		for (auto & cell : row)
		{
			cell.Render(render);
		}
	}
}



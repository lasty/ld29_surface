#ifndef TILES_MAP_H
#define TILES_MAP_H

#include <vector>
#include <map>

class Map;
class Tile;
class Renderer;


class Cell
{
public:
	Cell(Map *map, Tile &tile, int worldx, int worldy);

private:
	Map *map = nullptr;
	Tile *tile = nullptr;
	int worldx = 0;
	int worldy = 0;


public:
	void Render(Renderer &rend);
};


class Map
{
public:
	Map();

	void NewTileDef(const std::string &name, Tile &&tile);
	Tile & GetTileDef(const std::string &def);

	void NewMap(int width, int height, int tilesize, const std::string &blank);

	void Render(Renderer &render, int xoffset, int yoffset);

	void SetTile(int x, int y, const std::string &tilename);
private:

	int world_width = 0;
	int world_height = 0;
	int tile_size = 0;

	std::map<std::string, Tile> tile_defs;

	using Row = std::vector<Cell>;
	std::vector<Row> world;

	Row & GetRow(int r) { return world.at(r); }
	Cell & GetCell(int r, int c) { return GetRow(r).at(c); }
};

#endif // TILES_MAP_H

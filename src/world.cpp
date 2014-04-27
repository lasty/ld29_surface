
#include "world.h"

#include "tiles/tile.h"


World::World(Renderer &renderer)
: tiles{renderer, "data/tiles.png"}
{
	Tile t_grass{tiles, 32, 0, 0, 1, 1, 2};
	Tile t_sand{tiles, 32, 1, 0, 1, 1, 2};

	worldmap.NewTileDef("grass", std::move(t_grass));
	worldmap.NewTileDef("sand", std::move(t_sand));

	worldmap.NewMap(13, 7, 64, "grass");

	for (int i=0; i<10; i++)
	{
		worldmap.SetTile(i, 2, "sand");
	}
}

void World::Update(float dt)
{

}

void World::CheckForCollisions()
{

}

void World::CheckForDeadObjects()
{

}

void World::Render(Renderer &rend)
{
	RenderMap(rend);
	RenderObjects(rend);
}

void World::RenderMap(Renderer &rend)
{
	glm::ivec2 cam{0,0};
	worldmap.Render(rend, cam.x, cam.y);
}

void World::RenderObjects(Renderer &rend)
{
}

void World::AddObject(std::unique_ptr<Object> &&obj)
{
}



#ifndef WORLD_H
#define WORLD_H

#include "tiles/map.h"
#include "object.h"

#include <vector>
#include <memory>


class World
{
public:
	World(Renderer &rend);

private:
	Texture tiles;
	Map worldmap;

	std::vector<std::unique_ptr<Object>> objects;

public:
	void Update(float dt);

	void CheckForCollisions();

	void CheckForDeadObjects();

	void Render(Renderer &rend);

	void RenderMap(Renderer &rend);

	void RenderObjects(Renderer &rend);

	void AddObject(std::unique_ptr<Object> &&obj);

};

#endif // WORLD_H

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
	~World();

private:
	Texture tiles;
	Map worldmap;

	bool locked = false;

	std::vector<std::unique_ptr<Object>> objects;

	std::vector<std::unique_ptr<Object>> new_objects;
public:
	void Update(float dt);

	void DoCollide(Object &o1, Object &o2);
	void CheckForCollisions();
	void CheckForCollisionsFrom(Object &o);

	void CheckForDeadObjects();
	void CheckForNewObjects();

	void Render(Renderer &rend);

	void RenderMap(Renderer &rend);

	void RenderObjects(Renderer &rend);

	void AddObject(Object *obj);

};

#endif // WORLD_H

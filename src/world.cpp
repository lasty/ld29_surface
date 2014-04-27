
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

World::~World()
{
}

void World::Update(float dt)
{
	CheckForCollisions();

	CheckForDeadObjects();
	CheckForNewObjects();
}


#include <iostream>
using std::cout;
using std::endl;

void World::DoCollide(Object &o1, Object &o2)
{
/*	if (o1 == nullptr) { cout << "o1 is null" << endl; }
	if (o2 == nullptr) { cout << "o2 is null" << endl; }
	if (o1 == nullptr or o2 == nullptr) return;
*/

	glm::vec2 p1 = o1.GetPosition2();
	glm::vec2 p2 = o2.GetPosition2();

	float dist = glm::distance(p1, p2);
	dist -= o1.GetRadius();
	dist -= o2.GetRadius();

	if (dist < 0)
	{
		o1.Collide(o2);
	}
}


void World::CheckForCollisions()
{
	locked = true;
	for (auto outer=objects.begin(); outer != objects.end(); ++outer)
	{
		auto inner = outer;
		if (inner == objects.end()) break;
		inner++;
		if (inner == objects.end()) break;

		for (; inner != objects.end(); inner++)
		{
			DoCollide(*(*outer), *(*inner));
		}
	}
	locked = false;
}

void World::CheckForCollisionsFrom(Object &o)
{
	locked = true;
	for (auto inner=objects.begin(); inner != objects.end(); ++inner)
	{
		//if (inner->get() != o)  //<avoid self collision
		{
			Object &o2 = *(*inner);

			DoCollide(o, o2);
		}
	}
	locked = false;
}


void World::CheckForDeadObjects()
{
	auto it = objects.begin();

	while(it != objects.end())
	{
		if ((*it)->deleteme)
		{
			it = objects.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void World::CheckForNewObjects()
{
	for(auto it=new_objects.begin(); it != new_objects.end(); ++it)
	{
		objects.push_back( std::move(*it) );
	}
	new_objects.clear();
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
	for (auto &o : objects)
	{
		o->Render(rend);
	}
}

void World::AddObject(Object *obj)
{
	(locked ? new_objects : objects).emplace_back(obj);
}



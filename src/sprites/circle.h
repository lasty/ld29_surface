#ifndef SPRITES_CIRCLE_H
#define SPRITES_CIRCLE_H

#include "sdl/renderer.h"

#include <glm/glm.hpp>

#include <vector>

class Object;

class Circle
{
public:
	Circle(float radius, int num_points, bool elipse);

private:
	std::vector<glm::vec2> f_points;
	std::vector<SDL_Point> i_points;
	glm::ivec4 col { 255, 255, 255, 255 };

public:
	void SetColour(int r, int g, int b, int a);
	void Render(Renderer &rend, int x, int y, int zoom);
	void Render(Renderer &rend, Object &obj);
};


#endif // SPRITES_CIRCLE_H

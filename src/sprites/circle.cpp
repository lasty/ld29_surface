
#include "sprites/circle.h"

#include "sdl/sdl_headers.h"
#include "sdl/sdl_exception.h"

Circle::Circle(float radius, int num_points, bool elipse)
{
	for (int i=0; i <= num_points; i++)
	{
		float angle = float(i) / float(num_points) * 360.0f;
		float x = radius * cosf( glm::radians(angle) );
		float y = radius * sinf( glm::radians(angle) );
		if (elipse) y /= 2.333f;

		f_points.emplace_back( glm::vec2{ x, y } );
		i_points.emplace_back( SDL_Point{int(x),int(y)} );
	}
}


void Circle::SetColour(int r, int g, int b, int a)
{
	col.r = r;
	col.g = g;
	col.b = b;
	col.a = a;
}


void Circle::Render(Renderer &rend, int x, int y, int zoom)
{
	//manually do a matrix transform... I guess?
	for (unsigned i=0; i<f_points.size(); i++)
	{
		i_points[i].x = f_points[i].x * float(zoom) + float(x) - 0.375f;
		i_points[i].y = f_points[i].y * float(zoom) + float(y) - 0.375f;
	}

	rend.SetColour(col.r, col.g, col.b, col.a);

	int ret = SDL_RenderDrawLines(rend.GetRenderer(), &i_points[0], i_points.size());

	if (ret < 0)
	{
		throw SDLException("SDL_RenderLines");
	}
}



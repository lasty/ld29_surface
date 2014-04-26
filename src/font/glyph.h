#ifndef FONT_GLYPH_H
#define FONT_GLYPH_H

#include "font/face.h"
#include "sdl/surface.h"


class Glyph
{
public:
	Glyph(Face &face, const char ch);
	~Glyph() = default;

	Glyph(const Glyph &copy) = delete;
	Glyph(Glyph &&move) = default;
	Glyph& operator=(const Glyph &copyassign) = delete;
	Glyph& operator=(Glyph &&moveassign) = default;

	//TODO getters and setters maybe
	int width = 0;
	int height = 0;

	int bearingx = 0;
	int bearingy = 0;

	int advance = 0;

private:
	Surface surf;

public:
	const Surface & GetSurface() const { return surf; }
};


#endif // FONT_GLYPH_H

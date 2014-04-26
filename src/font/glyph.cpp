
#include "font/glyph.h"


Glyph::Glyph(Face &face, const char ch)
{

	//TODO fill this out

	width = 16;
	height = 24;

	bearingx = 4;
	bearingy = 8;

	advance = 20;

	surf = Surface{width, height};
}




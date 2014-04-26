
#include "font/glyph.h"


Glyph::Glyph(Face &face, const char ch)
{

	face.LoadAndRender(ch);

	width = face.GetBitmapWidth();
	height = face.GetBitmapHeight();

	bearingx = face.GetBearingX();
	bearingy = face.GetBearingY();

	advance = face.GetAdvance();

	if (width == 0 and height == 0)
	{
		blank = true;
		return;
	}

	surf = Surface{width, height};

	surf.Lock();
	for (int y=0; y<height; ++y)
	{
		for (int x=0; x<width; ++x)
		{
			auto grey = face.GetPixel(x,y);

			Uint8 r, g, b, a;
			r = g = b = 255;
			a = grey;

			surf.SetPixel(x, y, r, g, b, a);
		}
	}
	surf.Unlock();

}




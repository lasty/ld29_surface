
#include "font/font.h"

#include <algorithm>


Font::Font()
{
}


Font::Font(const std::string &font_filename, int font_size)
: face(font_filename, font_size)
{

}


Font::~Font()
{
}


bool Font::HasGlyph(char ch)
{
	auto it = glyphs.find(ch);
	return (it != glyphs.end());
}


Glyph& Font::GetGlyph(char ch)
{
	if (not HasGlyph(ch))
	{
		glyphs.emplace( std::make_pair( ch, Glyph(face, ch) ) );
	}

	return glyphs.at(ch);
}


const Surface & Font::GetGlyphSurface(char ch)
{
	Glyph &g = GetGlyph(ch);
	return g.GetSurface();
}


int Font::GetStringWidth(const std::string str)
{
	int width = 0;
	for (const char ch : str)
	{
		Glyph &g = GetGlyph(ch);
		width += g.advance;
	}
}


int Font::GetStringHeight(const std::string str)
{
	return face.GetLineHeight();
}


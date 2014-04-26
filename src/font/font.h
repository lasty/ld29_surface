#ifndef FONT_FONT_H
#define FONT_FONT_H

#include "font/face.h"

#include "font/glyph.h"

#include <map>

class Font
{
public:
	Font();
	Font(const std::string &font_filename, int font_size);
	~Font();

	Font(const Font &copy) = delete;
	Font(Font &&move) = default;
	Font& operator=(const Font &copyassign) = delete;
	Font& operator=(Font &&moveassign) = default;

private:
	Face face { };
	std::map<char, Glyph> glyphs;

public:
	const Face& GetFace() { return face; }

	bool HasGlyph(char ch);
	Glyph& GetGlyph(char ch);

	const Surface & GetGlyphSurface(char ch);

	int GetStringWidth(const std::string str);
	int GetStringHeight(const std::string str);
};


#endif // FONT_FONT_H

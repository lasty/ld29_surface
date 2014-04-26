#ifndef FONT_TEXT_H
#define FONT_TEXT_H

#include "font/font.h"

#include "sdl/surface.h"
#include "sdl/texture.h"

class Text
{
public:
	Text();
	Text(Renderer &rend, Font &font, const std::string &str);
	//~Text() = default;

	Text(const Text &copy) = delete;
	Text(Text &&move) = delete;

	Text& operator=(const Text &copyassign) = delete;
	Text& operator=(Text &&moveassign) = delete;

private:
	//Surface surf;
	Texture texture;
	std::string str;

	int width = 0;
	int height = 0;

public:
	//const Surface& GetSurface() const { return surf; }
	const Texture& GetTexture() const { return texture; }

	int GetWidth() const { return width; }
	int GetHeight() const { return width; }


	void SetText(Renderer &rend, Font &font, const std::string &str);

	void Render(Renderer &rend, int x, int y);
};

#endif // FONT_TEXT_H


#include "font/text.h"

Text::Text()
{
}

Text::Text(Renderer &rend, Font &font, const std::string &str)
{
	SetText(rend, font, str);
}

void Text::SetText(Renderer &rend, Font &font, const std::string &str)
{
	if (this->str == str) return;

	width = font.GetStringWidth(str);
	height = font.GetStringHeight(str);

	if (width == 0 or height == 0) return;

	Surface surf{width, height};

	SDL_SetSurfaceBlendMode(surf.GetSurface(), SDL_BLENDMODE_NONE);

	int x=0;
	int y=font.GetFace().GetBaseline();


	for (char ch : str)
	{
		Glyph &g = font.GetGlyph(ch);
		if (not g.blank)
		{
			const Surface &s = g.GetSurface();
			SDL_Rect dest;
			dest.x=x + g.bearingx;
			dest.y=y - g.bearingy;
			dest.w=g.width;
			dest.h=g.height;
			surf.Blit(s, nullptr, &dest);
		}
		x += g.advance;
	}


	texture = (Texture{rend, surf});
	SDL_SetTextureBlendMode(texture.GetTexture(), SDL_BLENDMODE_BLEND);
}


void Text::Render(Renderer &rend, int x, int y)
{
	SDL_Rect r;

	if (x < 0)
	{
		r.x = rend.GetWidth() - width;
	}
	else
	{
		r.x = x;
	}

	if (y < 0)
	{
		r.y = rend.GetHeight() - height;
	}
	else
	{
		r.y = y;
	}


	r.w = width;
	r.h = height;

	rend.Copy(texture, nullptr, &r);
}


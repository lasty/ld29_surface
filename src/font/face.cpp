
#include "font/face.h"
#include "font/freetype_exception.h"


Face::Face()
{

}


Face::Face(const std::string &font_filename, int font_size)
: font_size(font_size)
{
	const int index = 0;
	int err = FT_New_Face(library.GetLibrary(), font_filename.c_str(), index, &face);

	if (err)
	{
		throw FreetypeException(err, "FT_New_Face");
	}

	SetSize(font_size);
}


Face::~Face()
{
	if (face)
	{
		FT_Done_Face(face);
	}
}


Face::Face(Face &&move)
{
	std::swap(library, move.library);
	std::swap(face, move.face);
}


Face& Face::operator=(Face &&moveassign)
{
	std::swap(library, moveassign.library);
	std::swap(face, moveassign.face);

	return *this;
}

void Face::SetSize(int font_size)
{
	int err = FT_Set_Char_Size(face, font_size*64, font_size*64, 96, 96);
	if (err)
	{
		throw FreetypeException(err, "FT_Set_Char_Size");
	}

	this->font_size = font_size;
}


void Face::LoadAndRender(char ch)
{
	int err = FT_Load_Char(face, ch, FT_LOAD_DEFAULT);
	if (err)
	{
		throw FreetypeException(err, "FT_Load_Char");
	}

	if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
	{
		int err = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
		if (err)
		{
			throw FreetypeException(err, "FT_Render_Glyph");
		}

	}

	//setup pitch variable for Get Pixel
	pitch = abs(face->glyph->bitmap.pitch);
}


uint8_t Face::GetPixel(int x, int y) const
{
	if (x<0 or y<0 or x>=GetBitmapWidth() or y>=GetBitmapHeight())
		throw std::logic_error("Face::GetPixel : position out of range");

	const FT_Bitmap &bitmap = face->glyph->bitmap;

	unsigned index = (y * pitch) + x;
	return bitmap.buffer[index];
}

int Face::GetBearingX() const
{
	return face->glyph->bitmap_left;
}

int Face::GetBearingY() const
{
	return face->glyph->bitmap_top;
}

int Face::GetAdvance() const
{
	return face->glyph->advance.y / 64.0;
}

int Face::GetBitmapWidth() const
{
	return face->glyph->bitmap.width;
}

int Face::GetBitmapHeight() const
{
	return face->glyph->bitmap.rows;
}

int Face::GetLineHeight() const
{
	return face->size->metrics.height / 64.0;
}

int Face::GetBaseline() const
{
	return font_size;
}



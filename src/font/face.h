#ifndef FONT_FACE_H
#define FONT_FACE_H

#include "font/freetype_headers.h"

#include "font/library.h"

#include <string>

class Face
{
public:
	Face();
	Face(const std::string &font_filename, int font_size);
	~Face();
	Face(const Face &copy) = delete;
	Face(Face &&move);

	Face& operator=(const Face &copyassign) = delete;
	Face& operator=(Face &&moveassign);

private:
	Library library { };
	FT_Face face = nullptr;
	int pitch = 0;
	int font_size;

public:
	FT_Face GetFace() const { return face; }


	void SetSize(int font_size);

	void LoadAndRender(char ch);

	uint8_t GetPixel(int x, int y) const;


	int GetBearingX() const;
	int GetBearingY() const;

	int GetAdvance() const;

	int GetBitmapWidth() const;
	int GetBitmapHeight() const;

	int GetLineHeight() const;
	int GetBaseline() const;
};


#endif // FONT_FACE_H

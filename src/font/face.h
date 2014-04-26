#ifndef FONT_FACE_H
#define FONT_FACE_H

#include "font/freetype_headers.h"

#include "font/library.h"

#include <string>

class Face
{
public:
	Face();
	Face(const std::string &font_filename);
	~Face();
	Face(const Face &copy) = delete;
	Face(Face &&move);

	Face& operator=(const Face &copyassign) = delete;
	Face& operator=(Face &&moveassign);

private:
	Library library { };
	FT_Face face = nullptr;

public:
	FT_Face GetFace() const { return face; }

};


#endif // FONT_FACE_H

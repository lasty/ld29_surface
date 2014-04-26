
#include "font/face.h"
#include "font/freetype_exception.h"


Face::Face()
{

}


Face::Face(const std::string &font_filename)
{
	const int index = 0;
	int err = FT_New_Face(library.GetLibrary(), font_filename.c_str(), index, &face);

	if (err)
	{
		throw FreetypeException(err, "FT_New_Face");
	}
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




#include "font/library.h"

#include "font/freetype_exception.h"

Library::Library()
{
	int err = FT_Init_FreeType(&library);

	if (err)
	{
		throw FreetypeException(err, "FT_Init_FreeType");
	}
}


Library::~Library()
{
	if (library)
	{
		FT_Done_FreeType(library);
	}
}


Library::Library(Library &&move)
{
	std::swap(library, move.library);
}


Library& Library::operator=(Library &&moveassign)
{
	std::swap(library, moveassign.library);

	return *this;
}



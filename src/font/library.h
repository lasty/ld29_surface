#ifndef FONT_LIBRARY_H
#define FONT_LIBRARY_H

#include "font/freetype_headers.h"


class Library
{
public:
	Library();
	~Library();

	Library(const Library &copy) = delete;
	Library(Library &&move);

	Library& operator=(const Library &copyassign) = delete;
	Library& operator=(Library &&moveassign);

private:
	FT_Library library = nullptr;

public:
	FT_Library GetLibrary() const { return library; }

};

#endif // FONT_LIBRARY_H

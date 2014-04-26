
#include "font/freetype_exception.h"

#include <iostream>
#include <sstream>


FreetypeException::FreetypeException(int code, const std::string funcname)
: runtime_error(funcname.c_str())
{
	std::ostringstream msg;
	msg << "Freetype function " << funcname << " failed with code " << code;

	whatstr = msg.str();

	std::cerr << whatstr << std::endl;
}


const char* FreetypeException::what() const noexcept
{
	return whatstr.c_str();
}




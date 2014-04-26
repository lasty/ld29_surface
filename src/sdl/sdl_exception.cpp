
#include "sdl/sdl_exception.h"

#include "sdl/sdl_headers.h"

#include <iostream>
#include <sstream>


SDLException::SDLException(const std::string func)
: runtime_error(func.c_str())
{
	std::ostringstream msg;
	msg << func << " failed: " << SDL_GetError();

	whatmsg = msg.str();

	std::cerr << whatmsg << std::endl;
}

const char* SDLException::what() const noexcept
{
	return whatmsg.c_str();
}



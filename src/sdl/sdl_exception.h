#ifndef SDL_SDL_EXCEPTION_H
#define SDL_SDL_EXCEPTION_H

#include <stdexcept>
#include <string>


class SDLException : public std::runtime_error
{
public:
	SDLException(const std::string func);

	const char* what() const noexcept override;

private:
	std::string whatmsg;
};


#endif // SDL_SDL_EXCEPTION_H

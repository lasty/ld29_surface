#ifndef FONT_FREETYPE_EXCEPTION
#define FONT_FREETYPE_EXCEPTION

#include <stdexcept>
#include <string>


class FreetypeException : public std::runtime_error
{
public:
	FreetypeException(int code, const std::string funcname);

	const char* what() const noexcept override;

private:
	std::string whatstr;
};


#endif // FONT_FREETYPE_EXCEPTION

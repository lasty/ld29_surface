
#include "sdl/texture.h"

#include "sdl/surface.h"

#include "sdl/sdl_exception.h"


Texture::Texture()
{

}

Texture::Texture(const Renderer &rend, int width, int height)
{
	Uint32 format = SDL_PIXELFORMAT_RGBA8888;
	int access = SDL_TEXTUREACCESS_STATIC;
	texture = SDL_CreateTexture(rend.GetRenderer(), format, access, width, height);

	if (texture == nullptr)
	{
		throw SDLException("SDL_CreateTexture");
	}

	QueryTextureSize();
}

void Texture::QueryTextureSize()
{
	int ret = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	if (ret < 0)
	{
		throw SDLException("SDL_QueryTexture");
	}
}

Texture::Texture(const Renderer &rend, const Surface &surface)
{
	texture = SDL_CreateTextureFromSurface(rend.GetRenderer(), surface.GetSurface());

	if (texture == nullptr)
	{
		throw SDLException("SDL_CreateTextureFromSurface");
	}

	QueryTextureSize();
}

Texture::~Texture()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}
}

Texture::Texture(Texture &&move)
{
	std::swap(texture, move.texture);
	std::swap(width, move.width);
	std::swap(height, move.height);
}

Texture& Texture::operator=(Texture &&moveassign)
{
	std::swap(texture, moveassign.texture);
	std::swap(width, moveassign.width);
	std::swap(height, moveassign.height);

	return *this;
}


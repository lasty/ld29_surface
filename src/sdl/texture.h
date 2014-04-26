#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H

#include "sdl/renderer.h"

class Surface;

class Texture
{
public:
	Texture();
	Texture(const Renderer &rend, int width, int height);
	Texture(const Renderer &rend, const std::string &filename);
	Texture(const Renderer &rend, const Surface &surface);
	~Texture();

	Texture(const Texture &copy) = delete;
	Texture(Texture &&move);

	Texture& operator=(const Texture &copyassign) = delete;
	Texture& operator=(Texture &&moveassign);

private:
	SDL_Texture *texture = nullptr;
	int width = 0;
	int height = 0;

	void QueryTextureSize();

public:
	SDL_Texture* GetTexture() const { return texture; }

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	void SetBlend(bool blend = true);

};


#endif // SDL_TEXTURE_H

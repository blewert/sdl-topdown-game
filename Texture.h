#pragma once
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2.h"

class Texture
{
public:
	Texture() = default;
	Texture(SDL_Renderer* renderer, const std::string& path);
	~Texture();
	SDL_Texture* GetSDLTexture();
	void Render(const Vector2& position, int w = -1, int h = -1);
	void RenderRegion(const Vector2& screenPos, SDL_Rect& srcRegion, SDL_FPoint& dstDimensions);
	void FreeTexture();

	SDL_Point GetDimensions();

	static inline SDL_Texture* LoadFromDisk(SDL_Renderer* renderer, const std::string& path);

private:
	SDL_Texture* tex = nullptr;
	SDL_Renderer* renderer = nullptr;
	int width, height;
};


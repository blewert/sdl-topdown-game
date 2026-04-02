#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer, const std::string& path) : renderer(renderer)
{
    SDL_Texture* tex = Texture::LoadFromDisk(renderer, path);

    if (tex == nullptr)
    {
        SDL_Log("Couldn't load texture %s: %s", path.c_str(), IMG_GetError());
        return;
    }
    else
    {
        SDL_Log("Loaded texture %s from disk, (%d x %d)", path.c_str(), this->width, this->height);
    }
}

Texture::~Texture()
{
    FreeTexture();
}

SDL_Texture* Texture::GetSDLTexture()
{
    return this->tex;
}

void Texture::Render(const Vector2& position, int w, int h)
{
    if (w < 0)
        w = this->width;

    if (h < 0)
        h = this->height;

    SDL_FRect dstRect { position.x, position.y, w, h };
    SDL_RenderCopyF(this->renderer, this->tex, NULL, &dstRect);
}

void Texture::RenderRegion(const Vector2& screenPos, SDL_Rect& srcRegion, SDL_FPoint& dstDimensions)
{
    SDL_FRect dstRect{ screenPos.x, screenPos.y, dstDimensions.x, dstDimensions.y };
    SDL_RenderCopyF(this->renderer, this->tex, &srcRegion, &dstRect);
}

void Texture::FreeTexture()
{
    if (tex != nullptr)
    {
        SDL_DestroyTexture(tex);
        tex = nullptr;
    }
}

SDL_Point Texture::GetDimensions()
{
    return SDL_Point{ width, height };
}

inline SDL_Texture* Texture::LoadFromDisk(SDL_Renderer* renderer, const std::string& path)
{
    SDL_Surface* surf = IMG_Load(path.c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    SDL_FreeSurface(surf);

    return tex;
}

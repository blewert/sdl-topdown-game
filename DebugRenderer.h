#pragma once
#include "Renderer.h"
#include "Math.h"
#include "Texture.h"

class DebugRenderer : public Renderer
{
public:
	DebugRenderer(SDL_Renderer* renderer, GameObject* parent) : Renderer(renderer, parent, SDL_Rect{0, 0, 10, 10})
	{
		//TODO: Fix memory leak here with ctor being called per frame
		color = Random::Color();
	}

	void Render() override
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &bounds);
	}

private:
	SDL_Color color;
};


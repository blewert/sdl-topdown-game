#pragma once
#include "Renderer.h"
#include "Math.h"

class DebugRenderer : public Renderer
{
public:
	DebugRenderer(GameObject* parent) : Renderer(parent, SDL_Rect{0, 0, 10, 10})
	{
		color = Random::Color();
	}

	void Render(SDL_Renderer* renderer) override
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &bounds);
	}

private:
	SDL_Color color;
};


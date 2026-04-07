#pragma once
#include "SDL.h"
#include "Component.h"

class GameObject;

class Renderer : public Component
{
public:
	Renderer(SDL_Renderer* renderer, GameObject* parent, SDL_Rect bounds);
	virtual ~Renderer();

	virtual void Render() = 0;
	virtual void Update();

	SDL_Rect GetBounds() { return bounds;  }

protected:
	SDL_Rect bounds;
	SDL_Renderer* renderer;
};


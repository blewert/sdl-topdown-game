#pragma once
#include "SDL.h"
#include "Component.h"

class GameObject;

class Renderer : public Component
{
public:
	Renderer(GameObject* parent, SDL_Rect bounds);
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void Update();

protected:
	SDL_Rect bounds;
};


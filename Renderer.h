#pragma once
#include "SDL.h"
#include "Component.h"

class GameObject;

class Renderer : public Component
{
public:
	Renderer(SDL_Renderer* renderer, GameObject* parent, SDL_Rect bounds);
	virtual void Render() = 0;
	virtual void Update();

protected:
	SDL_Rect bounds;
	SDL_Renderer* renderer;
};


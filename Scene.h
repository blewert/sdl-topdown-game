#pragma once
#include "SDL.h"

class Scene
{
public:
	virtual void OnStart() = 0;
	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void OnEnd() = 0;
	virtual void Exit() = 0;
};


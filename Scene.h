#pragma once
#include "SDL.h"

class Scene
{
public:
	Scene(SDL_Renderer* renderer) : renderer(renderer) { }

	virtual void OnStart() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void OnEnd() = 0;
	virtual void Exit() = 0;
	
	SDL_Renderer* GetRenderer() { return renderer; }

protected:
	SDL_Renderer* renderer;
};


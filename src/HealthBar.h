#pragma once
#include "PlayerObject.h"

class HealthBar 
{
public:
	HealthBar(SDL_Renderer* renderer, PlayerObject* player);
	~HealthBar();

	void Render();

private:
	PlayerObject* player;
	SDL_Renderer* renderer;
	SDL_Window* window;

	int windowW, windowH;
};


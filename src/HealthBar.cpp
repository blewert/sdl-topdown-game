#include "HealthBar.h"

HealthBar::HealthBar(SDL_Renderer* renderer, PlayerObject* player)
{
	this->renderer = renderer;
	this->player = player;
	this->window = SDL_RenderGetWindow(renderer);

	SDL_GetWindowSize(window, &windowW, &windowH);
}

HealthBar::~HealthBar()
{

}

void HealthBar::Render()
{
	static int margin = 10;
	static int width = 100;
	static int height = 8;
	static int borderSize = 1;

	int x = margin;
	int y = margin;

	SDL_Rect targetRect = { x+borderSize, x+borderSize, width-borderSize*2, height-borderSize*2 };
	SDL_Rect borderRect = { x, y, width, height };

	float percent = fmaxf(0.0f, player->GetHealth() / 100.0f);
	targetRect.w *= percent;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, &borderRect);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderFillRect(renderer, &targetRect);
}

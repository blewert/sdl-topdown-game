#include "GameOverScene.h"

void GameOverScene::OnStart()
{
}

void GameOverScene::Update()
{
}

void GameOverScene::Render()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderClear(renderer);
}

void GameOverScene::OnEnd()
{
}

void GameOverScene::Exit()
{
}

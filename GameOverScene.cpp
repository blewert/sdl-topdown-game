#include "GameOverScene.h"

GameOverScene::GameOverScene(SDL_Renderer* renderer) : Scene(renderer)
{
	titleText = new Text(renderer, "Game over", "square-32");
	titleText->SetPosition(Vector2(10, 10));
}

GameOverScene::~GameOverScene()
{
	Exit();
}


void GameOverScene::Exit()
{
	delete titleText;
}


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

	titleText->Render();
}

void GameOverScene::OnEnd()
{
}

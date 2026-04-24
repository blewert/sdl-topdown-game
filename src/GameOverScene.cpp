#include "GameOverScene.h"
#include "Time.h"
#include "Game.h"
#include "GameScene.h"

GameOverScene::GameOverScene(SDL_Renderer* renderer) : Scene(renderer)
{
	int w, h;
	SDL_GetWindowSize(SDL_RenderGetWindow(renderer), &w, &h);

	titleText = new Text(renderer, "Game over", "square-72");
	titleText->SetPosition(Vector2(w / 2, h / 2) - Vector2::up * 150);
	titleText->SetAlign(TextAlign::Center);

	infoText = new Text(renderer, "Press R to restart the game.", "square-24");
	infoText->SetPosition(Vector2(w / 2, h / 2) - Vector2::up * 50);
	infoText->SetAlign(TextAlign::Center, TextAlign::Center);

	highScoreText = new Text(renderer, "", "pix-24");
	highScoreText->SetPosition(Vector2(w / 2, h / 2) + Vector2::up * 30);
	highScoreText->SetAlign(TextAlign::Center, TextAlign::Center);
}

GameOverScene::~GameOverScene()
{
	Exit();
}


void GameOverScene::Exit()
{
	delete titleText;
	delete infoText;
	delete highScoreText;
}


void GameOverScene::OnStart()
{
	std::string str;
	str = "You lasted " + std::to_string(Time::elapsedTime) + " seconds\n";
	str += "You eliminated " + std::to_string(Game::GetEnemiesKilled()) + " enemies";

	highScoreText->SetText(str);
}

void GameOverScene::Update()
{
	if (InputManager::Instance().FindBindingByName("R")->pressed)
	{
		SceneManager::Instance().ReloadScene("gameScene", new GameScene(renderer));
	}
}

void GameOverScene::Render()
{
	SDL_SetRenderDrawColor(renderer, 128, 128, 0, 0);
	SDL_RenderClear(renderer);

	titleText->Render();
	infoText->Render();
	highScoreText->Render();
}

void GameOverScene::OnEnd()
{
}

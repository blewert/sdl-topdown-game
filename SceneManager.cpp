#include "SceneManager.h"
#include "Game.h"
#include "DebugScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::~SceneManager()
{
	instance->Exit();
}

void SceneManager::Exit()
{
	SDL_Log("SceneManager::Exit()");

	for (auto& keyValue : sceneMap)
	{
		keyValue.second->Exit();
		delete keyValue.second;
	}
}

void SceneManager::AddScene(const std::string& sceneKey, Scene* scene)
{
	//Key must not already exist
	SDL_assert(sceneMap.find(sceneKey) == sceneMap.end());

	//Otherwise set it
	sceneMap[sceneKey] = scene;
}

void SceneManager::LoadScene(Game* game, const std::string& sceneKey)
{
	//Call OnEnd
	Scene* currentScene = game->GetCurrentScene();

	//Already a scene there? Call OnEnd
	if(currentScene != nullptr)
		currentScene->OnEnd();

	//Set scene and call start
	game->SetCurrentScene(sceneMap[sceneKey]);
	game->GetCurrentScene()->OnStart();
}

void SceneManager::LoadScene(const std::string& sceneKey)
{
	LoadScene(this->game, sceneKey);
}

void SceneManager::Initialise(Game* game, SDL_Renderer* renderer)
{
	this->game = game;

	//AddScene("debugScene", new DebugScene(renderer));
	AddScene("gameScene", new GameScene(renderer));
	AddScene("gameOverScene", new GameOverScene(renderer));
}

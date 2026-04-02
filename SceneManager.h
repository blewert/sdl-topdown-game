#pragma once
#include <string>
#include <map>
#include <iostream>
#include "Scene.h"

class Game;
class DebugScene;

class SceneManager
{
public:
	static inline SceneManager& Instance()
	{
		if (instance == nullptr)
			instance = new SceneManager();

		return *instance;
	}

	~SceneManager();

	void Exit();
	void AddScene(const std::string& sceneKey, Scene* scene);
	void LoadScene(Game* game, const std::string& sceneKey);
	void Initialise(Game* game, SDL_Renderer* renderer);

private:
	static SceneManager* instance;
	std::map<std::string, Scene*> sceneMap;
};


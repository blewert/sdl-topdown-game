#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DebugScene.h"

class Game
{
public:
	Game(int width, int height, bool fullScreen);
	~Game();

	void Update();
	void Render();
	void Exit();

	static void OnEnemySpawned() { enemiesCount++; }
	static void OnEnemyKilled() { enemiesKilled++; enemiesCount--; }
	static void ResetEnemyTallies() { enemiesKilled = 0; enemiesCount = 0; }
	static int GetEnemiesKilled() { return enemiesKilled; }

	static int GetEnemiesCurrentlySpawned() { return enemiesCount; }

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();

	bool NeedsExit();
	Scene* GetCurrentScene() const;
	void SetCurrentScene(Scene* scene);

private:
	void InitialiseSDL();
	void ExitSDL();
	void UpdateWindowTitle();

	Scene* currentScene;

	bool needsToExit = false;
	static bool sdlInitialised;
	static int enemiesKilled;
	static int enemiesCount;

	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};


#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"

class Game
{
public:
	Game(int width, int height, bool fullScreen);
	~Game();

	void Update();
	void Render();
	void Exit();

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();

	bool NeedsExit();
	Scene* GetCurrentScene() const;
	void SetCurrentScene(Scene* scene);

private:
	void InitialiseSDL();
	void ExitSDL();

	Scene* currentScene;

	bool needsToExit = false;
	static bool sdlInitialised;

	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};


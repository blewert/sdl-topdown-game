#pragma once
#include "SDL.h"
#include "SDL_image.h"

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

private:
	void InitialiseSDL();
	void ExitSDL();

	bool needsToExit = false;
	static bool sdlInitialised;

	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};


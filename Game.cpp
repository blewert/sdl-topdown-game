#include "Game.h"

bool Game::sdlInitialised = false;

Game::Game(int width, int height, bool fullScreen)
{
	//Invalid window size? Throw an error
	SDL_assert(width >= 0 && height >= 0);

	//Initialise SDL if not done already
	if (!sdlInitialised)
	{
		InitialiseSDL();
	}

	uint32_t wndFlags = SDL_WINDOW_SHOWN;

	if (fullScreen)
	{
		wndFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, wndFlags);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	SceneManager::Instance().Initialise(this);
}

Game::~Game()
{
	ExitSDL();
}

void Game::Update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			this->Exit();

		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			InputManager::Instance().Update(e);

		else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEMOTION)
			InputManager::Instance().Update(e);
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);



	SDL_RenderPresent(m_renderer);
}

void Game::Exit()
{
	needsToExit = true;
}

SDL_Window* Game::GetWindow()
{
	return nullptr;
}

SDL_Renderer* Game::GetRenderer()
{
	return nullptr;
}

bool Game::NeedsExit()
{
	return needsToExit;
}

Scene* Game::GetCurrentScene() const
{
	return currentScene;
}

void Game::SetCurrentScene(Scene* scene)
{
	this->currentScene = scene;
}

void Game::InitialiseSDL()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
}

void Game::ExitSDL()
{
	IMG_Quit();
	SDL_Quit();
}

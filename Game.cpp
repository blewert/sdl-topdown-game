#include "Game.h"
#include "Math.h"
#include "Time.h"
#include "TextureManager.h"
#include "VFXManager.h"

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

	Time::Initialise();
	Random::SeedRNG();
	
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, wndFlags);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	InputManager& instance = InputManager::Instance();
	instance.ShowCursor(false);

	TextureManager& texManager = TextureManager::Instance();
	texManager.Add("test-tex", "test.png", m_renderer);
	texManager.Add("test-anim", "test-anim.png", m_renderer);
	texManager.Add("reticle", "reticle.png", m_renderer);
	texManager.Add("player", "tank.png", m_renderer);
	texManager.Add("bullet", "bullet.png", m_renderer);
	texManager.Add("explosion1", "explosion1.png", m_renderer);
	texManager.Add("muzzleFlashBig", "muzzleFlashBig.png", m_renderer);
	texManager.Add("muzzleFlash", "muzzleFlash.png", m_renderer);
	texManager.Add("muzzleFlash2", "muzzleFlash2.png", m_renderer);

	SceneManager& sceneManager = SceneManager::Instance();
	sceneManager.Initialise(this, m_renderer);
	sceneManager.LoadScene(this, "gameScene");

	VFXManager* vfxManager = VFXManager::Initialise();
	vfxManager->LoadEffect(texManager["explosion1"], "explosion-1", 4, 1, Vector2(32, 32));
	vfxManager->LoadEffect(texManager["muzzleFlashBig"], "muzzleFlashBig", 2, 3, Vector2(64, 64));
	vfxManager->LoadEffect(texManager["muzzleFlash"], "muzzleFlash", 1, 1, Vector2(16, 16));
	vfxManager->LoadEffect(texManager["muzzleFlash2"], "muzzleFlash2", 1, 1, Vector2(16, 16));
}

Game::~Game()
{
	ExitSDL();

	SceneManager::Instance().Exit();
	InputManager::Instance().Exit();
	TextureManager::Instance().Exit();
}

void Game::Update()
{
	Time::Tick();
	InputManager::Instance().Update();

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			this->Exit();

		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			InputManager::Instance().ProcessEvent(e);

		else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEMOTION)
			InputManager::Instance().ProcessEvent(e);
	}

	static float timer = 0;
	timer += Time::deltaTime;

	if (timer >= 0.125f)
	{
		timer = Time::deltaTime;
		
		int w, h;
		char str[64];
		SDL_GetWindowSize(m_window, &w, &h);
		SDL_snprintf(str, 64, "Game [%d x %d], %.1f FPS. %.5f DT", w, h, Time::GetFPS(), Time::deltaTime);

		SDL_SetWindowTitle(m_window, str);
	}

	//SDL_SetWindowTitle(m_window, "")

	//SDL_Log("Ticks %d, Time %f, FPS %f\n", Time::deltaTicks, Time::deltaTime, Time::GetFPS());

	if (currentScene != nullptr)
		currentScene->Update();

	VFXManager::Update();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);

	currentScene->Render();
	VFXManager::Render(m_renderer);
	currentScene->PostRender();

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
	return m_renderer;
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

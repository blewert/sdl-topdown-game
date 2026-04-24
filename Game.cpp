#include "Game.h"
#include "Math.h"
#include "Time.h"
#include "TextureManager.h"
#include "VFXManager.h"
#include "Text.h"
#include "Timer.h"

bool Game::sdlInitialised = false;
int Game::enemiesKilled = 0;
int Game::enemiesCount = 0;

Game::Game(int width, int height, bool fullScreen)
{
	//Invalid window size? Throw an error
	SDL_assert(width >= 0 && height >= 0);

	//Initialise SDL if not done already
	if (!sdlInitialised)
	{
		InitialiseSDL();
	}

	//Set-up window flags
	uint32_t wndFlags = SDL_WINDOW_SHOWN;
	wndFlags |= (fullScreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;

	//Set defaults for timing system & RNG
	Time::Initialise();
	Random::SeedRNG();
	
	//Set-up SDL video
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, wndFlags);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "1");
	SDL_SetHint(SDL_HINT_VIDEO_DOUBLE_BUFFER, "1");

	//Set-up cursor params
	InputManager& inpManager = InputManager::Instance();
	inpManager.ShowCursor(false);
	SDL_SetRelativeMouseMode((SDL_bool)fullScreen);

	//----------
	
	//Load all textures into registry
	TextureManager& texManager = TextureManager::Instance();
	texManager.Add("tilemap", "images/tilemap.png", m_renderer);
	texManager.Add("test-tex", "images/test.png", m_renderer);
	texManager.Add("test-anim", "images/test-anim.png", m_renderer);
	texManager.Add("reticle", "images/reticle.png", m_renderer);
	texManager.Add("player", "images/tank.png", m_renderer);
	texManager.Add("bullet", "images/bullet.png", m_renderer);
	texManager.Add("explosion1", "images/explosion1.png", m_renderer);
	texManager.Add("muzzleFlashBig", "images/muzzleFlashBig.png", m_renderer);
	texManager.Add("muzzleFlash", "images/muzzleFlash.png", m_renderer);
	texManager.Add("muzzleFlash2", "images/muzzleFlash2.png", m_renderer);
	texManager.Add("enemy", "images/enemy.png", m_renderer);

	//Load all fonts into registry
	Text::LoadFont("square-24", "fonts/Square.ttf", 24);
	Text::LoadFont("square-32", "fonts/Square.ttf", 32);
	Text::LoadFont("square-48", "fonts/Square.ttf", 48);
	Text::LoadFont("square-72", "fonts/Square.ttf", 72);
	Text::LoadFont("pix-12", "fonts/Pix32.ttf", 12);
	Text::LoadFont("pix-16", "fonts/Pix32.ttf", 16);
	Text::LoadFont("pix-18", "fonts/Pix32.ttf", 18);
	Text::LoadFont("pix-24", "fonts/Pix32.ttf", 24);

	//Initialise all scenes, load game scene
	SceneManager& sceneManager = SceneManager::Instance();
	sceneManager.Initialise(this, m_renderer);
	sceneManager.LoadScene(this, "gameScene");

	//Initialise VFX manager with loaded textures
	VFXManager* vfxManager = VFXManager::Initialise();
	vfxManager->LoadEffect(texManager["explosion1"], "explosion-1", 4, 1, Vector2(32, 32));
	vfxManager->LoadEffect(texManager["muzzleFlashBig"], "muzzleFlashBig", 2, 3, Vector2(64, 64));
	vfxManager->LoadEffect(texManager["muzzleFlash"], "muzzleFlash", 1, 1, Vector2(16, 16));
	vfxManager->LoadEffect(texManager["muzzleFlash2"], "muzzleFlash2", 1, 1, Vector2(16, 16));
}

Game::~Game()
{
	//Quits SDL and all subsystems loaded
	ExitSDL();

	//Uninit all managers
	SceneManager::Instance().Exit();
	InputManager::Instance().Exit();
	TextureManager::Instance().Exit();
	Text::Exit();
}

void Game::Update()
{
	//Calculate new dt
	Time::Tick();

	//Update input prior to fresh events
	InputManager& inpManager = InputManager::Instance();
	inpManager.Update();

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		//Application quit: close button or ESC pressed
		if (e.type == SDL_QUIT || inpManager.FindBindingByName("Escape")->pressed)
			this->Exit();

		//Any key events: forward to input manager
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			inpManager.ProcessEvent(e);

		//Any mouse events: forward to input manager
		else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEMOTION)
			inpManager.ProcessEvent(e);
	}


	//Timer for updating window title
	static Timer timer = Timer(0.125f);

	//If the timer has hit an interval (seen above), update title
	if (timer.Tick())
		UpdateWindowTitle();

	//---

	if (currentScene != nullptr)
		currentScene->Update();

	VFXManager::Update();
}

void Game::Render()
{
	//Clear with a fresh background
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);

	//Render everything: the order of these calls matters
	//as we are also doing post render stuff.
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

void Game::UpdateWindowTitle()
{
	//Get width and height of window
	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);

	//Format it into an MBS; we are using an old school C MBS because 
	//it is easier to deal with precision
	char str[64];
	SDL_snprintf(str, 64, "Taster activity game [%d x %d], %.1f FPS. %.5f DT", w, h, Time::GetFPS(), Time::deltaTime);

	SDL_SetWindowTitle(m_window, str);
}

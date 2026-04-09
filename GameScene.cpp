#include "GameScene.h"
#include "GameObject.h"
#include "DebugObject.h"
#include "SDL.h"
#include "Math.h"
#include "TextureManager.h"
#include "Time.h"
#include "Rigidbody.h"
#include "InputManager.h"
#include "ReticleObject.h"
#include "SpriteRenderer.h"


GameScene::GameScene(SDL_Renderer* renderer) : Scene(renderer), inputManager(InputManager::Instance())
{
	SDL_Log("GameScene ctor");

	objects = new GameObjectList();

	this->reticle = new ReticleObject(this);
	objects->Add(reticle);

	camera = new Camera(this, 1.5f);
}

GameScene::~GameScene()
{
	this->Exit();
}

void GameScene::OnStart()
{
	objects->OnStart();
}

void GameScene::Update()
{
	objects->Update();
}

void GameScene::Render()
{
	objects->Render(renderer);
}

void GameScene::OnEnd()
{
	SDL_Log("GameScene::OnEnd");
	objects->OnEnd();
}

void GameScene::Exit()
{
	SDL_Log("GameScene::Exit");
	delete camera;
	delete reticle;
	delete objects;
}


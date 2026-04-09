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
#include "PlayerObject.h"

GameScene::GameScene(SDL_Renderer* renderer) : Scene(renderer), inputManager(InputManager::Instance())
{
	SDL_Log("GameScene ctor");

	objects = new GameObjectList();

	player = new PlayerObject(this);
	objects->Add(player);

	//Create reticle
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

	Vector2 camPos = camera->GetPosition();
	Vector2 playerPos = camera->LookAtPos(player->GetPosition());
	float camMoveSpeed = 100;

	camera->SetPosition(Vector2::MoveTowards(camPos, playerPos, 10000));

	//SDL_Log("%s", camera->GetPosition().ToString().c_str());
}

void GameScene::Render()
{
	objects->Render(renderer);
}

void GameScene::PostRender()
{
	objects->PostRender(renderer);
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


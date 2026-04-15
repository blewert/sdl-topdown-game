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
#include "BulletManager.h"

GameScene::GameScene(SDL_Renderer* renderer) : Scene(renderer), inputManager(InputManager::Instance())
{
	SDL_Log("GameScene ctor");

	objects = new GameObjectList();
	BulletManager::Initialise(this, 1000);

	player = new PlayerObject(this);
	objects->Add(player);

	//Create reticle
	this->reticle = new ReticleObject(this);
	objects->Add(reticle);

	camera = new Camera(this, 2.0f);
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

	Vector2 camPos = camera->GetPosition();
	Vector2 playerPos = player->GetPosition();
	Vector2 playerPosCam = camera->LookAtPos(playerPos);
	float camMoveSpeed = 100;

	//camera->SetPosition(Vector2::MoveTowards(camPos, playerPos, 100 * Time::deltaTime));
	//camera->SetPosition(Vector2(-20, -20));
	//camera->SetPosition(Vector2::left * SDL_sinf(Time::elapsedTime) * 100);

	Vector2 mousePos = inputManager.GetMouseNormScreenPos(GetCamera(), true);
	
	
	//playerPos = player->GetPosition();
	//Vector2 diff = playerPos - mousePos;

	//float angle = atan2(diff.y, diff.x) * Math::radToDeg;
	//angle += 90;

	Vector2 camOffsetPos = playerPosCam + mousePos * 25.0f;
	camera->SetPosition(camOffsetPos);

	//camera->SetPosition(playerPos);
	objects->Update();

	//SDL_Log("%s", camera->GetPosition().ToString().c_str())
	BulletManager::Update();
}

void GameScene::Render()
{
	objects->Render(renderer);
	BulletManager::Render();
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

	BulletManager::Exit();
}


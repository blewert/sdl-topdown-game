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
#include "VFXManager.h"
#include "EnemyObject.h"
#include "SceneManager.h"
#include "Game.h"

GameScene::GameScene(SDL_Renderer* renderer) : Scene(renderer), inputManager(InputManager::Instance())
{
	SDL_Log("GameScene ctor");

	//Initialise player & bullets
	objects = new GameObjectList();
	BulletManager::Initialise(this, 100);
	player = new PlayerObject(this);
	objects->Add(player);
	
	//Create tilemap
	tilemap = new Tilemap(this, renderer);
	tilemap->SetTexture(TextureManager::Instance()["tilemap"], 8, 6);
	tilemap->SetTileSize(16);
	tilemap->SetScale(2);
	tilemap->SetPlayerObject(player);
	player->SetTilemap(tilemap);

	//! Add code to load tilemap from disk here.
	tilemap->LoadFromDisk("data/map.json");

	//Create reticle
	this->reticle = new ReticleObject(this);
	objects->Add(reticle);

	//Create health bar
	hpBar = new HealthBar(renderer, player);
	hpText = new Text(renderer, "HP: 100", "pix-16");
	hpText->SetPosition(Vector2(20, 40));

	//Create camera
	camera = new Camera(this, 2.0f);
	VFXManager::SetCamera(camera);

	//Create enemy spawner
	spawner = new EnemySpawner("data/spawnpoints.json", this);

	//Reset enemy tallies back to normal
	Game::ResetEnemyTallies();
}

GameScene::~GameScene()
{
	this->Exit();
}

void GameScene::OnStart()
{
	Time::elapsedTime = 0.0f;
	objects->OnStart();
}

void GameScene::Update()
{
	spawner->Update();
	objects->Update();
	BulletManager::Update();

	//Set HP bar text
	hpText->SetText("HP: " + GetHPAsString());

	HandleCameraMovement();
}


void GameScene::HandleCameraMovement()
{
	//! Add code to handle camera movement here.
	float camMoveDist = 75.0f;

	Vector2 playerPos = GetPlayerPos();
	Vector2 mousePos = GetMouseScreenPos();

	//Set camera position
	Vector2 camOffsetPos = playerPos + mousePos * camMoveDist;
	camera->SetPosition(camOffsetPos);
}



void GameScene::Render()
{
	tilemap->Render();
	objects->Render(renderer);
	BulletManager::Render();
	hpBar->Render();
	hpText->Render();
}

void GameScene::PostRender()
{
	objects->PostRender(renderer);
	BulletManager::PostRender(renderer);
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
	delete hpBar;
	delete hpText;
	delete tilemap;
	delete spawner;

	//BulletManager::Exit();
}

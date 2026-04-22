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
	tilemap->SetMapSize(32, 32);
	tilemap->SetPosition(Vector2(0, 0));
	tilemap->SetTexture(TextureManager::Instance()["tilemap"], 8, 13);
	tilemap->SetTileSize(16);
	tilemap->SetScale(2);
	tilemap->SetPlayerObject(player);
	tilemap->Initialise();

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

	Game::ResetEnemiesKilled();

	for (int i = 0; i < 30; i++)
	{
		int x = i % 5;
		int y = i / 5;

		float xOff = x * 10;
		float yOff = y * 10;

		EnemyObject* testEnemy = new EnemyObject(this);
		testEnemy->SetPosition(Vector2(50 + xOff, 50 + yOff));
		objects->Add(testEnemy);
	}
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

	Vector2 camPos = camera->GetPosition();
	Vector2 playerPos = player->GetPosition();
	Vector2 playerPosCam = camera->LookAtPos(playerPos);
	float camMoveSpeed = 100;

	//camera->SetPosition(Vector2::MoveTowards(camPos, playerPos, 100 * Time::deltaTime));
	//camera->SetPosition(Vector2(-20, -20));
	//camera->SetPosition(Vector2::left * SDL_sinf(Time::elapsedTime) * 100);

	Vector2 mousePos = inputManager.GetMouseNormScreenPos(GetCamera(), true);

	hpText->SetText("HP: " + std::to_string((int)player->GetHealth()));
	
	if (InputManager::Instance().GetLeftMouseDownThisFrame() || player->GetHealth() <= 0.0f)
	{
		SceneManager::Instance().LoadScene("gameOverScene");
		return;
	}

	if (InputManager::Instance().GetRightMouseDownThisFrame())
	{
		Vector2 pos = InputManager::Instance().GetMouseWorldPos(GetCamera());

		for (int i = 0; i < 5; i++)
		{
			float randomScale = Random::Range(0.5f, 1.0f);
			Vector2 randomPos = pos + Random::InUnitCircle() * 20;

			VFXManager::SpawnEffect(randomPos, "explosion-1", 12, randomScale);
		}
	}


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

	//BulletManager::Exit();
}


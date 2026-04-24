#pragma once
#include "Scene.h"
#include "GameObjectList.h"
#include "HealthBar.h"
#include "Text.h"
#include "Tilemap.h"
#include "EnemySpawner.h"
#include "InputManager.h"
class ReticleObject;
class PlayerObject;

class GameScene : public Scene
{
public:
	GameScene(SDL_Renderer* renderer);
	~GameScene();

	// Inherited via Scene
	virtual void OnStart() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void OnEnd() override;
	virtual void Exit() override;

	Vector2 GetPlayerPos()
	{
		return camera->LookAtPos(player->GetPosition());
	}

	Vector2 GetMouseScreenPos()
	{
		return inputManager.GetMouseNormScreenPos(GetCamera(), true);
	}

	void HandleCameraMovement();

	std::string GetHPAsString()
	{
		std::string str = std::to_string(int(player->GetHealth()));
		return str;
	}

protected:
	InputManager& inputManager;
	
	ReticleObject* reticle;
	PlayerObject* player;

	HealthBar* hpBar;
	Text* hpText;

	Tilemap* tilemap;
	EnemySpawner* spawner;
};


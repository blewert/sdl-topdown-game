#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "MultipassRenderer.h"
#include "Tilemap.h"
#include "Timer.h"

class TextureManager;
class InputManager;

class PlayerObject : public GameObject
{
public:
	PlayerObject(Scene* parentScene);
	~PlayerObject();

	void FireBullet();
	void FireShell();

	void OnStart() override final;
	void Update() override final;

	void HandlePlayerFiring();
	void HandlePlayerMovement();
	void HandleTurretRotation();

	void Damage(float value);
	float GetHealth() { return health;  }
	void OnPlayerDie();

	void SetTilemap(Tilemap* tilemap) { this->tilemap = tilemap;  }

protected:
	TextureManager& texManager;
	InputManager& inputManager;
	Texture* playerTex;

	Tilemap* tilemap;

	SpriteRenderer* baseRenderer;
	SpriteRenderer* turretRenderer;

private:
	void SetupRenderers();
	Timer gunTimer;
	float lastShellTime = 0;
	float health = 100.0f;
	bool playerDead = false;

};


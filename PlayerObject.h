#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "MultipassRenderer.h"

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

	void Damage(float value);
	float GetHealth() { return health;  }
	void OnPlayerDie();


protected:
	TextureManager& texManager;
	InputManager& inputManager;
	Texture* playerTex;

	SpriteRenderer* baseRenderer;
	SpriteRenderer* turretRenderer;

private:
	void SetupRenderers();
	float gunTimer = 0;
	float lastShellTime = 0;
	float health = 100.0f;
	bool playerDead = false;

};


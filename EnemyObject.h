#pragma once
#include "GameObject.h"

#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "MultipassRenderer.h"

class TextureManager;
class InputManager;

class EnemyObject : public GameObject
{
public:
	EnemyObject(Scene* parentScene);
	~EnemyObject();

	void OnStart() override final;
	void Update() override final;


protected:
	TextureManager& texManager;
	InputManager& inputManager;
	Texture* enemyTex;

private:
	float gunTimer = 0;
	float lastShellTime = 0;

	GameObject* playerObj;
};



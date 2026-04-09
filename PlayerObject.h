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

	void OnStart() override final;
	void Update() override final;

protected:
	TextureManager& texManager;
	InputManager& inputManager;
	Texture* playerTex;

	SpriteRenderer* baseRenderer;
	SpriteRenderer* turretRenderer;

private:
	void SetupRenderers();

};


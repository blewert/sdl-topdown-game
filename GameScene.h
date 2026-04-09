#pragma once
#include "Scene.h"
#include "GameObjectList.h"

class InputManager;
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

protected:
	InputManager& inputManager;

	GameObjectList* objects;
	ReticleObject* reticle;
	PlayerObject* player;
};


#pragma once
#include "SDL.h"
#include "GameObjectList.h"
#include "Scene.h"

class GameObject;

class DebugScene : public Scene
{
public:
	DebugScene(SDL_Renderer* renderer);
	~DebugScene();

	virtual void OnStart();
	virtual void Update();
	virtual void OnEnd();
	virtual void Exit();
	virtual void Render();

	GameObjectList* objects;
};


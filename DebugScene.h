#pragma once
#include "SDL.h"
#include "GameObjectList.h"
#include "Scene.h"

class GameObject;

class DebugScene : public Scene
{
public:
	DebugScene();
	~DebugScene();

	virtual void OnStart();
	virtual void Update();
	virtual void OnEnd();
	virtual void Exit();
	virtual void Render(SDL_Renderer* renderer);

	GameObjectList objects;
};


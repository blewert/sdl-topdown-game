#pragma once
#include <vector>
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

	std::vector<GameObject>* objects;
};


#pragma once
#include "Scene.h"


class DebugScene : public Scene
{
public:
	DebugScene();
	~DebugScene();

	virtual void OnStart();
	virtual void Update();
	virtual void OnEnd();
	virtual void Exit();
};


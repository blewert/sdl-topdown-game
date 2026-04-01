#pragma once
#include "GameObject.h"

class DebugObject : public GameObject
{
public:
	DebugObject(Scene* scene);
	~DebugObject();

	void OnStart() override final;
	void Update() override final;

private:
	int timer;
};


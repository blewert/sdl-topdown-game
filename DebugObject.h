#pragma once
#include "GameObject.h"
#include "ComponentList.h"
#include "DebugRenderer.h"

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


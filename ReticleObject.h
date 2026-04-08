#pragma once
#include "GameObject.h"
#include "ComponentList.h"

class InputManager;

class ReticleObject : public GameObject
{
public:
	ReticleObject(Scene* scene);
	~ReticleObject();

	void OnStart() override final;
	void Update() override final;

	void SetVisible(bool status);

private:
	InputManager& GetInputManager();
};


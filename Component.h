#pragma once

class GameObject;

class Component
{
public:
	Component(GameObject* parent);
	~Component() = default;

	virtual void Update() = 0;

	virtual void OnAttach() {}
	virtual void OnDetach() {}

	bool pendingDelete = false;
	GameObject* parent;
};


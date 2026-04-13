#pragma once

class GameObject;

class Component
{
public:
	Component() = default;
	Component(GameObject* parent);
	virtual ~Component() = default;

	virtual void Update() = 0;

	virtual void OnAttach() {}
	virtual void OnDetach() {}

	bool pendingDelete = false;
	GameObject* parent;

	bool enabled = true;
};


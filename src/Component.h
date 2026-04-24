#pragma once

class GameObject;

class Component
{
public:
	Component(GameObject* parent);
	virtual ~Component() = default;

	virtual void Update() = 0;

	virtual void OnAttach() {}
	virtual void OnDetach() {}

	void SetDeallocOnRemoval(bool deallocOnRemoval) { this->deallocOnRemoval = deallocOnRemoval; }
	bool GetDeallocOnRemoval() { return deallocOnRemoval; }

	bool pendingDelete = false;
	GameObject* parent;

	bool enabled = true;

private: 
	bool deallocOnRemoval = true;
};


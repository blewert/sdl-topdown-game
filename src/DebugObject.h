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

	void OnCollisionEnter(Rigidbody& thisRb, Rigidbody& otherRb) override;
	void OnCollisionExit(Rigidbody& thisRb, Rigidbody& otherRb) override;

private:
	int timer;
	float angle;
	Vector2 initialPos;
};


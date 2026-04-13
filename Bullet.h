#pragma once
#include "GameObject.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include <optional>

class Bullet : public GameObject
{
public:
	Bullet(const Vector2& initialPos, const Vector2& initialVelocity, Scene* parentScene);
	~Bullet();

	void Update() override;

	bool IsAlive() { return isAlive; }

private:
	std::optional<Rigidbody> rb;
	std::optional<BoxCollider> bc;
	bool isAlive = true;
};


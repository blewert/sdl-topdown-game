#pragma once
#include "GameObject.h"
#include "Rigidbody.h"
#include "BoxCollider.h"

class Bullet : public GameObject
{
public:
	Bullet(const Vector2& initialPos, const Vector2& initialVelocity, Scene* parentScene);
	~Bullet();


private:
	Rigidbody rb;
	BoxCollider bc;
};


#pragma once
#include "Component.h"
#include "Vector2.h"
#include "BoxCollider.h"
#include <map>

class Rigidbody : public Component
{
public:
	Rigidbody() { };
	Rigidbody(GameObject* parent, BoxCollider& collider);
	~Rigidbody() override;

	virtual void Update() override;

	void SetVelocity(const Vector2& velocity);
	void SetStatic(const bool status);
	void SetKinematic(const bool status);
	void SetDragFactor(const float factor);

	void HandleCollisionEvents(Rigidbody& other, bool colliding);

	inline bool IsCollidingWith(Rigidbody& other);

	inline Vector2 GetVelocity() const;
	inline bool IsStatic() const;
	inline bool IsKinematic() const;

	static bool IsCollidingAABB(Rigidbody& a, Rigidbody& b);

private:
	Vector2 velocity;
	bool isStatic;
	bool isKinematic;
	float dragFactor;
	BoxCollider colliderRef;

	std::map<uint64_t, int> collisionFrameMap;
};


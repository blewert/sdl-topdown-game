#pragma once
#include "GameObject.h"
#include "Rigidbody.h"
#include "BoxCollider.h"
#include <optional>
#include "SpriteRenderer.h"


class Bullet : public GameObject
{
public:
	Bullet(const Vector2& initialPos, const Vector2& initialVelocity, Scene* parentScene);
	~Bullet();

	void Update() override;
	void Reset(const Vector2& pos, const Vector2& velocity);


	void PostRender(SDL_Renderer* renderer) override final
	{
		//Rigidbody* rb = components->rigidbody;
		//rb->DebugRender(renderer);
	}

	bool IsAlive() { return isAlive; }
	void SetAlive(bool alive) { isAlive = alive; }

private:
	std::optional<Rigidbody> rb;
	std::optional<BoxCollider> bc;

	bool isAlive = true;
	float timer = 0.0f;

	friend class BulletManager;
};


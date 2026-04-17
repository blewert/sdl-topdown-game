#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "MultipassRenderer.h"
#include "Rigidbody.h"
#include "Bullet.h"

class TextureManager;
class InputManager;

class EnemyObject : public GameObject
{
public:
	EnemyObject(Scene* parentScene);
	~EnemyObject();

	void OnStart() override final;
	void Update() override final;

	void OnCollisionEnter(Rigidbody& thisRb, Rigidbody& otherRb) override final
	{
		Bullet* bulletObj = dynamic_cast<Bullet*>(otherRb.parent);

		if (bulletObj == nullptr)
			return;

		OnCollisionWithBullet(thisRb, bulletObj);
	}

	void OnCollisionWithBullet(Rigidbody& thisRb, Bullet* bulletObj);
	
	void PostRender(SDL_Renderer* renderer) override final
	{
		//Rigidbody* rb = components->rigidbody;
		//rb->DebugRender(renderer);
	}

	void ApplyHurtEffect(float timeSeconds, const SDL_Color& color);

protected:
	TextureManager& texManager;
	InputManager& inputManager;
	Texture* enemyTex;

private:
	float health = 100.0f;
	float gunTimer = 0;
	float lastShellTime = 0;
	float hurtTimer = 0;
	SDL_Color hurtColor = { 255, 0, 0, 255 };
	SpriteRenderer* sprRenderer;

	GameObject* playerObj;
};



#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "MultipassRenderer.h"
#include "Rigidbody.h"
#include "Bullet.h"
#include "PlayerObject.h"
#include "Game.h"
#include "VFXManager.h"

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
		if (otherRb.parent->GetTag() == "shell")
		{
			OnCollisionWithShell(thisRb, otherRb);
			return;
		}

		Bullet* bulletObj = dynamic_cast<Bullet*>(otherRb.parent);

		if (bulletObj == nullptr)
			return;

		OnCollisionWithBullet(thisRb, bulletObj);
	}

	void OnCollisionStay(Rigidbody& thisRb, Rigidbody& otherRb) override final
	{
		if (otherRb.parent->GetTag() == "shell")
			OnCollisionWithShell(thisRb, otherRb);
	}

	void OnEnemyDie();
	void OnCollisionWithShell(Rigidbody& thisRb, Rigidbody& otherRb);
	void OnCollisionWithBullet(Rigidbody& thisRb, Bullet* bulletObj);
	
	void HandleAttackPlayer();
	Vector2 GetDirectionToPlayer() { return playerObj->GetPosition() - GetPosition(); }
	Vector2 GetPlayerPos() { return playerObj->GetPosition(); }

	void HandleHurtTimerEffect()
	{
		if (hurtTimer > 0)
		{
			hurtTimer -= Time::deltaTime;
			sprRenderer->SetRenderMod(RenderMod().WithActivated(true).WithColor(hurtColor));
		}
		else
		{
			sprRenderer->SetRenderMod(RenderMod().WithActivated(false));
		}

	}
	
	void PostRender(SDL_Renderer* renderer) override final
	{
		//Rigidbody* rb = components->rigidbody;
		//rb->DebugRender(renderer);
	}

	void ApplyHurtEffect(float timeSeconds, const SDL_Color& color)
	{
		hurtTimer = timeSeconds;
		hurtColor = color;
	}


protected:
	TextureManager& texManager;
	InputManager& inputManager;
	Texture* enemyTex;

private:
	float health = 100.0f;
	float speed = 1.0f;
	float hurtTimer = 0;
	Timer damageTimer;
	SDL_Color hurtColor = { 255, 0, 0, 255 };
	SpriteRenderer* sprRenderer;
	PlayerObject* playerObj;
};



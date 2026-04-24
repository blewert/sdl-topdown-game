#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "MultipassRenderer.h"
#include "Tilemap.h"
#include "Timer.h"
#include "InputManager.h"
#include "VFXManager.h"
#include "Math.h"

class TextureManager;

class PlayerObject : public GameObject
{
public:
	PlayerObject(Scene* parentScene);
	~PlayerObject();

	void FireBullet();
	void FireShell();

	void OnStart() override final;
	void Update() override final;

	void HandlePlayerFiring();
	void HandlePlayerMovement();
	void HandleTurretRotation();

	void Damage(float value);
	float GetHealth() { return health;  }
	void OnPlayerDie();

	void SetTilemap(Tilemap* tilemap) { this->tilemap = tilemap;  }

	void DrawMuzzleFlash(const Vector2& pos, float angle)
	{
		for (int i = 0; i < 2; i++)
		{
			Vector2 explosionPos = pos;
			explosionPos += Random::InUnitCircle() * 5;
			VFXManager::SpawnEffect(explosionPos, "explosion-1", 8, 0.125f);
		}

		if (Random::Value() >= 0.5f)
			VFXManager::SpawnEffect(pos, "muzzleFlash", 24, 1.0f, angle + 90);
		else
			VFXManager::SpawnEffect(pos, "muzzleFlash2", 24, 1.0f, angle + 90);
	}

	void DrawTracerLines(const Vector2& pos, const Vector2& fireDir)
	{
		for (int i = 0; i < 5; i++)
		{
			Vector2 randomStartPos = pos + fireDir * Random::Range(0.0f, 400.0f);
			Vector2 randomEndPos = randomStartPos + fireDir * Random::Range(0.0, 32.0f);

			uint32_t col = 0xffff00ff;

			if (Random::Value() <= 0.2f)
				col = 0xffffffff;

			VFXManager::DrawLine(randomStartPos, randomEndPos, col, 0.05f);
		}
	}

	Vector2 GetFireDirection()
	{
		Vector2 playerPos = GetPosition();
		Vector2 mousePosWorld = GetMousePosWorld();
		return (mousePosWorld - playerPos).Normalized();

	}

	Vector2 GetShellSpawnPos(float offset=0.0f)
	{
		Vector2 playerPos = GetPosition();
		Vector2 dir = GetFireDirection();
		return playerPos + dir * (15 + offset);
	}

	Vector2 GetBulletSpawnPos(float offset=0.0f)
	{
		return GetShellSpawnPos(-5 + offset);
	}

	Vector2 GetMousePosWorld()
	{
		return inputManager.GetMouseWorldPos(parentScene->GetCamera());
	}

protected:
	TextureManager& texManager;
	InputManager& inputManager;
	Texture* playerTex;

	Tilemap* tilemap;

	SpriteRenderer* baseRenderer;
	SpriteRenderer* turretRenderer;

private:
	void SetupRenderers();
	Timer gunTimer;
	float lastShellTime = 0;
	float health = 100.0f;
	bool playerDead = false;

};


#include "PlayerObject.h"
#include "Scene.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Math.h"
#include "Rigidbody.h"
#include "BulletManager.h"
#include "VFXManager.h"

PlayerObject::PlayerObject(Scene* parentScene) 
	: GameObject(parentScene), inputManager(InputManager::Instance()), texManager(TextureManager::Instance())
{
	components = new ComponentList();

	this->SetName("player");
	this->SetTag("player");

	this->SetPosition(Vector2(0, 0));

	this->SetupRenderers();
}

PlayerObject::~PlayerObject()
{
	delete components;
	delete renderer;

	delete renderer;
	delete baseRenderer;
	delete turretRenderer;
}

void PlayerObject::FireBullet()
{
	Vector2 playerPos = GetPosition();
	Vector2 mousePosWorld = inputManager.GetMouseWorldPos(parentScene->GetCamera());

	Vector2 direction = (mousePosWorld - playerPos).Normalized();
	float origAngle = SDL_atan2f(direction.y, direction.x) * Math::radToDeg;
	float angle = origAngle + Random::Range(-4.0f, 4.0f);

	Vector2 fireDirection = Vector2::FromPolar(angle, 1.0f).Normalized();
	fireDirection *= 450;

	Vector2 spawnPos = playerPos + direction * 10;

	BulletManager::FireBullet(spawnPos, fireDirection);


	for (int i = 0; i < 2; i++)
	{
		Vector2 explosionPos = spawnPos + direction * 3;
		explosionPos += Random::InUnitCircle() * 5;
		VFXManager::SpawnEffect(explosionPos, "explosion-1", 8, 0.125f);
	}

	if(Random::Value() >= 0.5f)
		VFXManager::SpawnEffect(spawnPos + direction * 3, "muzzleFlash", 24, 1.0f, origAngle + 90);
	else
		VFXManager::SpawnEffect(spawnPos + direction * 3, "muzzleFlash2", 24, 1.0f, origAngle + 90);


	for (int i = 0; i < 5; i++)
	{
		Vector2 fireDir = fireDirection.Normalized();
		Vector2 randomStartPos = spawnPos + fireDir * Random::Range(0.0f, 100.0f);
		Vector2 randomEndPos = randomStartPos + fireDir * Random::Range(0.0, 32.0f);

		uint32_t col = 0xffff00ff;

		if (Random::Value() <= 0.2f)
			col = 0xffffffff;

		VFXManager::DrawLine(randomStartPos, randomEndPos, col, 0.05f);
	}
}

void PlayerObject::HandlePlayerFiring()
{
	if (inputManager.GetRightMouseDownThisFrame())
		gunTimer = 0.0f;

	if (inputManager.GetRightMouseDown())
	{
		gunTimer += Time::deltaTime;

		if (gunTimer >= 0.05f)
		{
			gunTimer = Time::deltaTime;
			SDL_Log("Firing gun bullet");
			FireBullet();
		}
	}

	if (inputManager.GetLeftMouseDownThisFrame())
	{
		if (Time::elapsedTime - lastShellTime >= 2.0f)
		{
			SDL_Log("Firing bullet");
			lastShellTime = Time::elapsedTime;
		}
	}
}

void PlayerObject::OnStart()
{

}

void PlayerObject::Update()
{
	components->Update();

	Vector2 mousePos = inputManager.GetMouseWorldPos(parentScene->GetCamera());
	Vector2 playerPos = GetPosition();
	Vector2 diff = playerPos - mousePos;

	float angle = atan2(diff.y, diff.x) * Math::radToDeg;
	angle += 90;

	turretRenderer->SetAngle(angle);

	Vector2 movementVec = inputManager.Find2DAxisByName("WASD")->value;

	HandlePlayerFiring();


	//baseRenderer->DrawLine(GetPosition(), GetPosition() + Vector2::right * 100);

	if (movementVec == Vector2::zero)
		return;

	float targetAng = baseRenderer->GetAngle() + movementVec.x;

	float ang2 = Math::MoveTowards(baseRenderer->GetAngle(), targetAng, 155 * Time::deltaTime);
	baseRenderer->SetAngle(ang2);

	Vector2 tankFwdVec = Vector2::FromPolar(turretRenderer->GetAngle() + 90, 1.0f);
	Vector2 tankMoveVec = Vector2::FromPolar(ang2 + 90, 1.0f);
	SetPosition(GetPosition() + tankMoveVec * movementVec.y * Time::deltaTime * 50);

	Vector2 pos = GetPosition();

	baseRenderer->DrawLine(pos, pos + tankMoveVec.Normalized() * 250, 0xff00ffff);
	//baseRenderer->DrawLine(pos, pos + tankFwdVec.Normalized() * 250, 0x00ff00ff);

	//SDL_SetRenderDrawColor(parentScene->GetRenderer(), 255, 0, 0);
	//SDL_RenderDrawLine(parentScene->GetRenderer(), pos.x, pos.y, pos.x + tankMoveVec.x, pos.y + tankMoveVec.y);
}

void PlayerObject::SetupRenderers()
{
	this->playerTex = texManager["player"];

	SDL_FRect rct = SDL_FRect{ 0, 0, 32, 48 };

	this->baseRenderer = new SpriteRenderer(parentScene->GetRenderer(), this, rct);
	this->turretRenderer = new SpriteRenderer(parentScene->GetRenderer(), this, rct);

	SpriteAnimationParams commonParams = SpriteAnimationParams().WithDimensions({ 32, 48 }).WithRowCols(1, 2);
	SpriteAnimationParams animParamsBase = SpriteAnimationParams(commonParams).WithOffset(true, 0);
	SpriteAnimationParams animParamsTurret = SpriteAnimationParams(animParamsBase).WithOffset(true, 1);

	baseRenderer->SetAnimated(false, animParamsBase);
	baseRenderer->SetTexture(playerTex);
	baseRenderer->SetPivot(SpriteRendererPivot::Center);

	turretRenderer->SetAnimated(false, animParamsTurret);
	turretRenderer->SetTexture(playerTex);
	turretRenderer->SetPivot(SpriteRendererPivot::Center);
	turretRenderer->SetCustomRotatePivot(true, { 16, 20 });

	this->renderer = new MultipassRenderer(this, { baseRenderer, turretRenderer });
}

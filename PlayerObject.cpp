#include "PlayerObject.h"
#include "Scene.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Math.h"
#include "Rigidbody.h"
#include "BulletManager.h"
#include "VFXManager.h"
#include "EnemyObject.h"
#include "ShellCollisionObject.h"

PlayerObject::PlayerObject(Scene* parentScene) 
	: GameObject(parentScene), inputManager(InputManager::Instance()), texManager(TextureManager::Instance())
{
	components = new ComponentList();

	this->SetName("player");
	this->SetTag("player");

	this->SetPosition(Vector2(100, 100));

	this->SetupRenderers();

	gunTimer = Timer(0.1f);
}

PlayerObject::~PlayerObject()
{
	delete components;
	delete renderer;
	delete baseRenderer;
	delete turretRenderer;
}

void PlayerObject::FireShell()
{
	Vector2 playerPos = GetPosition();
	Vector2 mousePosWorld = inputManager.GetMouseWorldPos(parentScene->GetCamera());

	Vector2 direction = (mousePosWorld - playerPos).Normalized();
	float origAngle = SDL_atan2f(direction.y, direction.x) * Math::radToDeg;
	float angle = origAngle + Random::Range(-2.0f, 2.0f);

	Vector2 fireDirection = Vector2::FromPolar(angle, 1.0f).Normalized();
	fireDirection *= 250;

	Vector2 spawnPos = playerPos + direction * 15;
	VFXManager::SpawnEffect(spawnPos + direction * 3, "muzzleFlashBig", 24, 1.0f, origAngle + 90);
	VFXManager::SpawnEffect(spawnPos + direction * 3, "explosion-1", 24, 1.0f, origAngle + 90);

	VFXManager::CameraShake(0.25f, 10);

	parentScene->AddObject(new ShellCollisionObject(inputManager.GetMousePos(), 30, parentScene));
}


void PlayerObject::FireBullet()
{
	Vector2 playerPos = GetPosition();
	Vector2 mousePosWorld = inputManager.GetMouseWorldPos(parentScene->GetCamera());

	Vector2 direction = (mousePosWorld - playerPos).Normalized();
	float origAngle = SDL_atan2f(direction.y, direction.x) * Math::radToDeg;
	float angle = origAngle + Random::Range(-2.0f, 2.0f);

	Vector2 fireDirection = Vector2::FromPolar(angle, 1.0f).Normalized();
	fireDirection *= 250;
	
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
		Vector2 randomStartPos = spawnPos + fireDir * Random::Range(0.0f, 400.0f);
		Vector2 randomEndPos = randomStartPos + fireDir * Random::Range(0.0, 32.0f);

		uint32_t col = 0xffff00ff;

		if (Random::Value() <= 0.2f)
			col = 0xffffffff;

		VFXManager::DrawLine(randomStartPos, randomEndPos, col, 0.05f);
	}
}


void PlayerObject::Damage(float value)
{
	if (playerDead)
		return;

	this->health -= value;

	if (this->health <= 0.0f)
	{
		playerDead = true;
		OnPlayerDie();
	}
}

void PlayerObject::OnPlayerDie()
{
	SDL_Log("You died");
	SceneManager::Instance().LoadScene("gameOverScene");
}

void PlayerObject::OnStart()
{

}




void PlayerObject::HandlePlayerFiring()
{
	if (inputManager.GetRightMouseDown())
	{
		if (gunTimer.Tick())
		{
			FireBullet();
		}
	}

	if (inputManager.GetLeftMouseDownThisFrame())
	{
		if (Time::elapsedTime - lastShellTime >= 2.0f)
		{
			//SDL_Log("Firing bullet");
			lastShellTime = Time::elapsedTime;
			FireShell();
		}
	}
}


void PlayerObject::HandlePlayerMovement()
{
	//Get input movement direction
	Vector2 movementVec = inputManager.Find2DAxisByName("WASD")->value;

	//No movement? We don't have to do anything
	if (movementVec == Vector2::zero)
		return;

	//---------
	//Some movement parameters
	float tankRotationSpeed = 150;
	float tankMoveSpeed = 50;

	//Otherwise get target angle to move to
	float targetAng = baseRenderer->GetAngle() + movementVec.x;

	//And move towards this 
	float lerpAngle = Math::MoveTowards(baseRenderer->GetAngle(), targetAng, tankRotationSpeed * Time::deltaTime);
	baseRenderer->SetAngle(lerpAngle);

	//Calculate forward & movement vector 
	Vector2 tankFwdVec = Vector2::FromPolar(turretRenderer->GetAngle() + 90, 1.0f);
	Vector2 tankMoveVec = Vector2::FromPolar(lerpAngle + 90, 1.0f);
	Vector2 tankPos = GetPosition();

	//And from this, figure out
	Vector2 targetPos = tankPos + tankMoveVec * movementVec.y * Time::deltaTime * tankMoveSpeed;

	//If this target position is going to collide -- then we shouldn't move! Return early
	if (tilemap->CollidingWithPoint(targetPos))
		return;

	//Otherwise, set position to this new target
	baseRenderer->DrawLine(tankPos, tankPos + tankMoveVec.Normalized() * 250, 0xff00ffff);
	SetPosition(targetPos);
}

void PlayerObject::HandleTurretRotation()
{
	//Get positions of player & mouse
	Vector2 mousePos = inputManager.GetMouseWorldPos(parentScene->GetCamera());
	Vector2 playerPos = GetPosition();

	//Find angle along this vector, set the turret to look along it
	float angle = Math::AngleBetween(playerPos, mousePos) + 90;
	turretRenderer->SetAngle(angle);
}

void PlayerObject::Update()
{
	components->Update();

	HandlePlayerFiring();
	HandleTurretRotation();
	HandlePlayerMovement();
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

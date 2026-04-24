#include "PlayerObject.h"
#include "Scene.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Rigidbody.h"
#include "BulletManager.h"
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
	//! Add code to fire a shell here.
}


void PlayerObject::FireBullet()
{
	//! Add code to fire a bullet here.
}


void PlayerObject::Damage(float value)
{
	//! Add code to damage player here.
}

void PlayerObject::OnPlayerDie()
{
	SDL_Log("You died");
	
	//! Add code to load game over screen here.
}

void PlayerObject::OnStart()
{

}


void PlayerObject::HandlePlayerFiring()
{
	//Add code here to fire a bullet
	//Add code here to fire a shell
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

	//! Add code to calculate new player position, and move them, here.

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

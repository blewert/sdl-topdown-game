#include "EnemyObject.h"
#include "Scene.h"
#include "GameObjectList.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "VFXManager.h"
#include "Math.h"
#include "Game.h"

EnemyObject::EnemyObject(Scene* parentScene) 
	: GameObject(parentScene), inputManager(InputManager::Instance()), texManager(TextureManager::Instance())
{
	components = new ComponentList();

	Game::OnEnemySpawned();

	this->SetName("enemy");
	this->SetTag("enemy");

	this->SetPosition(Vector2(0, 0));

	this->enemyTex = texManager["enemy"];
	SDL_FRect rct = SDL_FRect{ 0, 0, 16, 16 };
	
	SpriteAnimationParams animParams = SpriteAnimationParams();
	animParams = animParams.WithFPS(12).WithTexture(enemyTex).WithRowCols(2, 2);

	sprRenderer = new SpriteRenderer(parentScene->GetRenderer(), this, rct);
	sprRenderer->SetTexture(this->enemyTex);
	sprRenderer->SetAnimated(true, SpriteAnimationParams().WithFPS(12).WithDimensions({ 16, 16 }).WithRowCols(2, 2));
	sprRenderer->SetRandomStartFrame();

	BoxCollider bc = BoxCollider(this, rct);
	components->Pop();
	Rigidbody* rb = new Rigidbody(this, bc);

	parentScene->GetObjects()->AddRigidbody(rb);

	this->damageTimer = Timer(0.5f);
	this->speed = Random::Range(10, 20);
	this->renderer = sprRenderer;	
}

EnemyObject::~EnemyObject()
{
	delete components;
	delete renderer;
}

void EnemyObject::OnStart()
{
	this->playerObj = dynamic_cast<PlayerObject*>(parentScene->GetObjects()->FindFirstObjectByTag("player"));
	SDL_assert(this->playerObj != nullptr);
}

void EnemyObject::Update()
{
	//Not yet dead? Update all components
	if(health > 0)
		components->Update();

	//Move towards the player
	Vector2 dirToPlayerNorm = GetDirectionToPlayer().Normalized();
	components->rigidbody->SetVelocity(dirToPlayerNorm * speed);
	
	//Apply hurt effect
	HandleHurtTimerEffect();
	HandleAttackPlayer();
}

void EnemyObject::HandleAttackPlayer()
{
	//Attack parameters & dir to player
	float enemyAttackRadius = 25.0f;
	float enemyDamageAmount = Random::Range(1.0f, 1.5f);

	Vector2 dirToPlayer = GetDirectionToPlayer();

	//Not in range of player? Skip the rest of this function
	if (dirToPlayer.Magnitude() > enemyAttackRadius)
		return;

	//-----
	//Stop the enemy
	components->rigidbody->SetVelocity(Vector2::zero);

	if (damageTimer.Tick())
	{
		//Damage the player
		playerObj->Damage(enemyDamageAmount);

		//Find a random position around the player and spawn an effect
		Vector2 vfxSpawnPos = GetPlayerPos();
		vfxSpawnPos += Random::InUnitCircle() * 10;
		VFXManager::SpawnEffect(vfxSpawnPos, "explosion-1", 12, 0.5f);
	}
}


void EnemyObject::OnCollisionWithShell(Rigidbody& thisRb, Rigidbody& otherRb)
{
	//Spawn effects
	VFXManager::SpawnEffect(GetPosition() + Vector2(4, 4), "explosion-1");

	//Kill this enemy
	OnEnemyDie();
}

void EnemyObject::OnCollisionWithBullet(Rigidbody& thisRb, Bullet* bulletObj)
{
	//Get positions
	Vector2 thisPosition = GetPosition();
	Vector2 bulletPosition = bulletObj->GetPosition();

	//Delete bullet: release back into pool
	bulletObj->SetAlive(false);

	//Damage the enemy
	this->health -= 35.0f;

	//Explosions and VFX
	VFXManager::SpawnEffect(bulletPosition, "explosion-1", 12, 0.25f);
	this->ApplyHurtEffect(0.1f, SDL_Color { 255, 0, 0, 255 });

	if (this->health <= 0.0f)
	{
		OnEnemyDie();
	}
}


void EnemyObject::OnEnemyDie()
{
	//Delete this enemy
	this->Destroy();

	//Notify game that this enemy has died, for the kill count
	Game::OnEnemyKilled();

	//-----
	// 
	//VFX: shake camera and add an explosion
	VFXManager::SpawnEffect(GetPosition() + Vector2(4, 4), "explosion-1");
	VFXManager::CameraShake(0.05f, 2);

	//Add more explosions!
	for (int i = 0; i < 5; i++)
	{
		Vector2 randomPos = GetPosition() + Random::InUnitCircle() * 10;
		VFXManager::SpawnEffect(randomPos, "explosion-1", 16, Random::Range(0.25f, 0.5f));
	}
}


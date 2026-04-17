#include "EnemyObject.h"
#include "Scene.h"
#include "GameObjectList.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "VFXManager.h"
#include "Math.h"

EnemyObject::EnemyObject(Scene* parentScene) 
	: GameObject(parentScene), inputManager(InputManager::Instance()), texManager(TextureManager::Instance())
{
	components = new ComponentList();

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

	BoxCollider bc = BoxCollider(this, rct);
	components->Pop();
	Rigidbody* rb = new Rigidbody(this, bc);
	//components->rigidbody = rb;

	parentScene->GetObjects()->AddRigidbody(rb);

	this->renderer = sprRenderer;	
}

EnemyObject::~EnemyObject()
{
	delete components;
	delete renderer;
}

void EnemyObject::OnStart()
{
	this->playerObj = parentScene->GetObjects()->FindFirstObjectByTag("player");

	SDL_assert(this->playerObj != nullptr);
}

void EnemyObject::Update()
{
	components->Update();

	Vector2 dirToPlayer = this->playerObj->GetPosition() - GetPosition();
	dirToPlayer.Normalize();

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

void EnemyObject::OnCollisionWithBullet(Rigidbody& thisRb, Bullet* bulletObj)
{
	Vector2 thisPosition = GetPosition();
	Vector2 bulletPosition = bulletObj->GetPosition();

	VFXManager::SpawnEffect(bulletPosition, "explosion-1", 12, 0.25f);
	bulletObj->SetAlive(false);

	this->ApplyHurtEffect(0.05f, SDL_Color { 255, 0, 0, 255 });
	SDL_Log("Collision!");

	this->health -= 15.0f;

	/*SDL_Log("%f", health);*/

	if (this->health <= 0.0f)
	{
		this->Destroy();
		VFXManager::SpawnEffect(GetPosition()+Vector2(4, 4), "explosion-1");

		for (int i = 0; i < 5; i++)
		{
			Vector2 randomPos = GetPosition() + Random::InUnitCircle() * 10;
			VFXManager::SpawnEffect(randomPos, "explosion-1", 16, Random::Range(0.25f, 0.5f));
		}
	}
}

void EnemyObject::ApplyHurtEffect(float timeSeconds, const SDL_Color& color)
{
	hurtTimer = timeSeconds;
	hurtColor = color;
}

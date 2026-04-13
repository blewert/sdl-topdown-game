#include "Bullet.h"
#include "Scene.h"
#include "GameObjectList.h"
#include "Time.h"

Bullet::Bullet(const Vector2& initialPos, const Vector2& initialVelocity, Scene* parentScene)
	: GameObject(parentScene)
{
	components = new ComponentList();

	this->SetName("bullet");
	this->SetTag("bullet");

	bc.emplace(this, SDL_FRect { 0, 0, 8, 8 });
	rb.emplace(this, bc.value());	

	parentScene->GetObjects()->AddRigidbody(&rb.value());

	this->SetPosition(initialPos);
	this->rb.value().SetVelocity(initialVelocity);

	SDL_Log("Bullet ctor, ID %d", id);
}

Bullet::~Bullet()
{
	if(components != nullptr)
		delete components;
}

void Bullet::Update()
{
	components->Update();

	timer += Time::deltaTime;

	if (timer >= 5.0f)
	{
		this->isAlive = false;
	}
}

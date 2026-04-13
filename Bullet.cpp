#include "Bullet.h"
#include "Scene.h"
#include "GameObjectList.h"

Bullet::Bullet(const Vector2& initialPos, const Vector2& initialVelocity, Scene* parentScene)
	: GameObject(parentScene)
{
	components = new ComponentList();

	this->SetName("bullet");
	this->SetTag("bullet");

	bc = BoxCollider(this, { 0, 0, 8, 8 });
	rb = Rigidbody(this, bc);	

	parentScene->GetObjects()->AddRigidbody(&rb);

	this->SetPosition(initialPos);
	this->rb.SetVelocity(initialVelocity);

	SDL_Log("Bullet ctor, ID %d", id);
}

Bullet::~Bullet()
{
	delete components;
}

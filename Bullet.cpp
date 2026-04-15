#include "Bullet.h"
#include "Scene.h"
#include "GameObjectList.h"
#include "Time.h"
#include "TextureManager.h"

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

	//TODO: Fix this to remove need for manual pop; this is because
	//		the component constructor expects heap alloc'd mem not stack alloc'd.
	//		This is inflexible and ideally needs a separate fix.
	SDL_FRect bounds { 0, 0, 4, 4 };

	SpriteRenderer* tmpRenderer = new SpriteRenderer(parentScene->GetRenderer(), this, bounds);
	this->renderer = tmpRenderer;

	Texture* tex = TextureManager::Instance()["bullet"];
	tmpRenderer->SetTexture(tex);
	tmpRenderer->SetAnimated(false, SpriteAnimationParams().WithRowCols(1, 1).WithTexture(tex));
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

	if (timer >= 1.0f)
	{
		this->isAlive = false;
	}
}

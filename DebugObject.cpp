#include "DebugObject.h"
#include "SDL.h"
#include "Math.h"
#include "Time.h"
#include "Scene.h"
#include "SpriteRenderer.h"
#include "TextureManager.h"
#include "Rigidbody.h"

DebugObject::DebugObject(Scene* parentScene) : GameObject(parentScene)
{
	components = new ComponentList();
	
	//renderer = new DebugRenderer(parentScene->GetRenderer(), this);

	SDL_Rect rct = SDL_Rect{ 0, 0, 32, 32 };
	renderer = new SpriteRenderer(parentScene->GetRenderer(), this, rct);

	SpriteAnimationParams animParams;
	animParams.columns = 6;
	animParams.rows = 3;
	animParams.fps = 12;
	animParams.frameH = 32;
	animParams.frameW = 32;

	Texture* tex = TextureManager::Instance()["test-anim"];

	SpriteRenderer* spriteRenderer = (SpriteRenderer*)renderer;
	spriteRenderer->SetAnimated(true, animParams);
	spriteRenderer->SetTexture(tex);

	timer = Random::Range(90, 100);
	components->Add(renderer);

	initialPos = Vector2(500, 400);
	SetPosition(initialPos);
}

DebugObject::~DebugObject()
{
	delete components;
	delete renderer;
}

void DebugObject::OnStart()
{
	GameObject::OnStart();
	angle = Random::Range(0.0f, 360.0f);
}

void DebugObject::Update()
{
	GameObject::Update();

	angle = fmodf(angle + 100 * Time::deltaTime, 360);

	float d = 50;
	float x = cosf(angle * Math::degToRad) * d;
	float y = sinf(angle * Math::degToRad) * d;

	//SetPosition(initialPos + Vector2(x, y));
}

void DebugObject::OnCollisionEnter(Rigidbody& thisRb, Rigidbody& otherRb)
{
	SDL_Log("Start collision with %d and %d", thisRb.parent->id, otherRb.parent->id);
}

void DebugObject::OnCollisionExit(Rigidbody& thisRb, Rigidbody& otherRb)
{
	SDL_Log("Exit collision with %d and %d", thisRb.parent->id, otherRb.parent->id);
}

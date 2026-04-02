#include "DebugObject.h"
#include "SDL.h"
#include "Math.h"
#include "Time.h"
#include "Scene.h"

DebugObject::DebugObject(Scene* parentScene) : GameObject(parentScene)
{
	components = new ComponentList();
	
	renderer = new DebugRenderer(parentScene->GetRenderer(), this);
	timer = Random::Range(90, 100);
	components->Add(renderer);

	initialPos = Random::PositionInRect(0, 0, 800, 600);
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

	SetPosition(initialPos + Vector2(x, y));
	
	if (this->id == 5)
	{
		SDL_Log("angle %f", angle);
	}

	timer--;

	if (timer <= 0)
		this->Destroy();
}

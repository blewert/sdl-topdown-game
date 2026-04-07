#include "DebugScene.h"
#include "GameObject.h"
#include "DebugObject.h"
#include "SDL.h"
#include "Math.h"
#include "TextureManager.h"
#include "Time.h"
#include "Rigidbody.h"
#include "InputManager.h"

DebugScene::DebugScene(SDL_Renderer* renderer) : Scene(renderer)
{
	SDL_Log("DebugScene ctor");

	objects = new GameObjectList();
	
	GameObject* testObj = new DebugObject(this);
	Rigidbody* rb = new Rigidbody(testObj);
	objects->Add(testObj);
	objects->AddRigidbody(rb);

	rb->SetDragFactor(0.5f);
	rb->SetVelocity(Vector2(-75, 0));

	//for (int i = 0; i < 100; i++)
	//{
	//	auto* obj = new DebugObject(this);
	//	objects->Add(obj);
	//	obj->SetPosition(Random::PositionInRect(0, 0, 800, 600));
	//}

	camera = new Camera(this, 1.0f);
}

DebugScene::~DebugScene()
{
	this->Exit();
}

void DebugScene::OnStart()
{
	SDL_Log("DebugScene::OnStart");
	objects->OnStart();
}

void DebugScene::Update()
{
	objects->Update();

	static float timer = 0.0f;
	timer += Time::deltaTime;

	//Vector2 calcPos = Vector2::FromPolar(timer * 55.0f, 50);
	Vector2 direction = Vector2::FromPolar(timer * 25.0f, 1);

	direction.x = roundf(direction.x);
	direction.y = roundf(direction.y);



	//Vector2 calcPos = camera->GetPosition() + direction * Time::deltaTime * 35;
	//camera->SetPosition(calcPos);
}

void DebugScene::OnEnd()
{
	SDL_Log("DebugScene::OnEnd");
	objects->OnEnd();
}

void DebugScene::Exit()
{
	SDL_Log("DebugScene::Exit");
	delete camera;
}

void DebugScene::Render()
{
	objects->Render(renderer);
}

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
	BoxCollider* bc = new BoxCollider(testObj, SDL_Rect{ 0, 0, 32, 32 });
	Rigidbody* rb = new Rigidbody(testObj, bc);
	objects->Add(testObj);
	objects->AddRigidbody(rb);

	rb->SetDragFactor(0.5f);
	rb->SetVelocity(Vector2(-125, 0));

	GameObject* testObj2 = new DebugObject(this);
	BoxCollider* bc2 = new BoxCollider(testObj2, SDL_Rect { 0, 0, 32, 32 });
	Rigidbody* rb2 = new Rigidbody(testObj2, bc2);
	objects->Add(testObj2);
	objects->AddRigidbody(rb2);
	testObj2->SetPosition(testObj->GetPosition() + Vector2::left * 150);

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

#include "EnemyObject.h"
#include "Scene.h"
#include "GameObjectList.h"
#include "InputManager.h"
#include "TextureManager.h"

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

	SpriteRenderer* sprRenderer = new SpriteRenderer(parentScene->GetRenderer(), this, rct);
	sprRenderer->SetTexture(this->enemyTex);
	sprRenderer->SetAnimated(true, SpriteAnimationParams().WithFPS(12).WithDimensions({ 16, 16 }).WithRowCols(2, 2));

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
}

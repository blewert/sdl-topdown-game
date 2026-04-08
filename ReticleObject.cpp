#include "ReticleObject.h"
#include "SDL.h"
#include "Math.h"
#include "Scene.h"
#include "SpriteRenderer.h"
#include "TextureManager.h"
#include "InputManager.h"

ReticleObject::ReticleObject(Scene* scene) : GameObject(scene)
{
	components = new ComponentList();

	SDL_Rect rct = SDL_Rect{ 0, 0, 32, 32 };
	renderer = new SpriteRenderer(parentScene->GetRenderer(), this, rct);

	Texture* tex = TextureManager::Instance()["reticle"];

	SpriteRenderer* spriteRenderer = (SpriteRenderer*)renderer;
	SpriteAnimationParams params = SpriteAnimationParams().WithTexture(tex).WithRowCols(1, 1);
	spriteRenderer->SetPivot(SpriteRendererPivot::Center);
	spriteRenderer->SetAnimated(false, params);
	spriteRenderer->SetTexture(tex);
	
	SetVisible(true);
}

ReticleObject::~ReticleObject()
{
	delete components;
	delete renderer;
}

void ReticleObject::OnStart()
{
}

void ReticleObject::Update()
{
	GameObject::Update();

	Vector2 mousePos = GetInputManager().GetMousePos();
	Camera* camera = parentScene->GetCamera();

	SetPosition(camera->WorldToScreenPos(mousePos));
}

void ReticleObject::SetVisible(bool status)
{
	renderer->enabled = status;
}

InputManager& ReticleObject::GetInputManager()
{
	return InputManager::Instance();
}

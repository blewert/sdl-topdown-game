#include "Camera.h"
#include "Scene.h"

Camera::Camera(Scene* parentScene, float pixelScale) : GameObject(parentScene)
{
	//It should be the case that this constructor is only
	//called once: there should only be one camera in the
	//scene at any time
	SDL_assert(parentScene->GetCamera() == nullptr);

	//Set the camera for this scene
	parentScene->SetCamera(this);

	//Set up instance variables
	this->pixelScale = pixelScale;
	this->SetPosition(Vector2(0, 0));

	//Set scale
	SDL_RenderSetScale(parentScene->GetRenderer(), pixelScale, pixelScale);
}

Camera::~Camera()
{
	
}

SDL_Rect Camera::CalculateBounds(SDL_Rect& inputRect)
{
	Vector2 pos = GetPosition();
	return SDL_Rect{ inputRect.x - (int)pos.x, inputRect.y - (int)pos.y, inputRect.w, inputRect.h };
}

Vector2 Camera::WorldToScreenPos(Vector2& pos)
{
	return GetPosition() + pos / this->pixelScale;
}

Vector2 Camera::ScreenToWorldPos(Vector2& pos)
{
	return GetPosition() - pos / this->pixelScale;
}

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

	SDL_Window* window = SDL_RenderGetWindow(parentScene->GetRenderer());
	SDL_GetWindowSize(window, &windowW, &windowH);
}

Camera::~Camera()
{
	
}

void Camera::Update()
{
	SDL_Log("Camera update");
}

SDL_FRect Camera::CalculateBounds(SDL_FRect& inputRect)
{
	Vector2 pos = WorldToScreenPos(GetPosition());
	Vector2 convInput = WorldToScreenPos(Vector2(inputRect.x, inputRect.y));

	return SDL_FRect{ convInput.x - pos.x, convInput.y - pos.y, (float)inputRect.w, (float)inputRect.h };
}

Vector2 Camera::WorldToScreenPos(const Vector2& pos)
{
	SDL_Renderer* renderer = parentScene->GetRenderer();
	Vector2 logicalPos = pos - GetPosition();

	int screenX, screenY;
	SDL_RenderLogicalToWindow(renderer, logicalPos.x, logicalPos.y, &screenX, &screenY);

	return Vector2(screenX, screenY);
}

Vector2 Camera::ScreenToWorldPos(const Vector2& pos)
{
	SDL_Renderer* renderer = parentScene->GetRenderer();

	float logicalX, logicalY;
	SDL_RenderWindowToLogical(renderer, pos.x, pos.y, &logicalX, &logicalY);

	return Vector2(logicalX, logicalY) + GetPosition();
}

void Camera::SetPosition(const Vector2& newPosition)
{
	this->position = newPosition;
}

Vector2 Camera::LookAtPos(const Vector2& position)
{
	return Vector2(position) - GetCameraCentreOffsetWorld();
}

Vector2 Camera::GetCameraCentreOffsetWorld()
{
	float w, h;
	SDL_RenderWindowToLogical(parentScene->GetRenderer(), windowW / 2, windowH / 2, &w, &h);

	return Vector2(w, h) / pixelScale;
}

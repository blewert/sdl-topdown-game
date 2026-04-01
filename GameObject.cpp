#include "GameObject.h"
#include "Scene.h"

GameObject::GameObject(Scene* parentScene)
{
	this->parentScene = parentScene;
}

void GameObject::SetPosition(const Vector2& newPosition)
{
	position = newPosition;
}

Vector2 GameObject::GetPosition()
{
	return position;
}

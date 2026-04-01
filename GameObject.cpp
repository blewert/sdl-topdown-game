#include "GameObject.h"
#include "Scene.h"

int GameObject::objId = 0;

GameObject::GameObject(Scene* parentScene)
{
	this->parentScene = parentScene;
	this->id = objId++;
}

GameObject::~GameObject()
{

}

void GameObject::SetPosition(const Vector2& newPosition)
{
	position = newPosition;
}

Vector2 GameObject::GetPosition()
{
	return position;
}

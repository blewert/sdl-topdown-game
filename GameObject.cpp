#include "GameObject.h"
#include "Scene.h"
#include "Camera.h"

uint64_t GameObject::objId = 0;

GameObject::GameObject(Scene* parentScene)
{
	this->parentScene = parentScene;
	this->id = objId++;

	//Give default name and tag
	this->name = "obj-" + std::to_string(this->id);
	this->tag = "default";
}

GameObject::~GameObject()
{
	if (this->components != nullptr)
		delete this->components;

	if (this->renderer != nullptr)
		delete this->renderer;
}

void GameObject::SetPosition(const Vector2& newPosition)
{
	position = newPosition;
}

Vector2 GameObject::GetPosition()
{
	return position;
}

void GameObject::OnCollisionEnter(Rigidbody& thisRb, Rigidbody& otherRb)
{
}

void GameObject::OnCollisionExit(Rigidbody& thisRb, Rigidbody& otherRb)
{
}

void GameObject::OnCollisionStay(Rigidbody& thisRb, Rigidbody& otherRb)
{
}

#include "Component.h"
#include "GameObject.h"
#include "Rigidbody.h"

Component::Component(GameObject* parent) : parent(parent)
{
	//Attach to component list
	parent->components->Add(this);
	this->OnAttach();
}

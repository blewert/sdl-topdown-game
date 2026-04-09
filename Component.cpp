#include "Component.h"
#include "GameObject.h"
#include "Rigidbody.h"

Component::Component(GameObject* parent) : parent(parent)
{
	//Attach to component list
	if(parent->components != nullptr)
		parent->components->Add(this);

	this->OnAttach();
}

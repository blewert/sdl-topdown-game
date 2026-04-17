#include "Component.h"
#include "GameObject.h"
#include "Rigidbody.h"

Component::Component(GameObject* parent) : parent(parent)
{
	//TODO: Remove this to make attachment manual
	// 
	//Attach to component list
	if(parent->components != nullptr)
		parent->components->Add(this);

	this->OnAttach();
}

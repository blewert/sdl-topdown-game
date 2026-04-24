#include "ComponentList.h"
#include "Component.h"
#include "Rigidbody.h"

void ComponentList::Add(Component* component)
{
	//TODO: Make this nicer, casting is a bit grim
	if (dynamic_cast<Rigidbody*>(component))
		this->rigidbody = dynamic_cast<Rigidbody*>(component);

	components.push_back(component);
}

void ComponentList::Pop()
{
	components.pop_back();
}

void ComponentList::Update()
{
	bool needsCull = false;

	for (Component* component : components)
	{
		component->Update();

		if (component->pendingDelete)
			needsCull = true;
	}

	if(needsCull)
		CullPendingDeleteComponents();
}

void ComponentList::CullPendingDeleteComponents()
{
	std::vector<Component*> tmpObjs;

	for (int i = 0; i < components.size(); i++)
	{
		//If not pending delete, add to temp list
		if (!components[i]->pendingDelete)
			tmpObjs.push_back(components[i]);

		else
		{
			//Otherwise, call destructor: this will no longer exist
			components[i]->OnDetach();

			if(components[i]->GetDeallocOnRemoval())
				delete components[i];
		}
	}

	//Then swap the underlying values
	std::swap(this->components, tmpObjs);
}

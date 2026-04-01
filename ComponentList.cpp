#include "ComponentList.h"
#include "Component.h"

void ComponentList::Add(Component* component)
{
	component->OnAttach();
	components.push_back(component);
}

void ComponentList::Update()
{
	for (Component* component : components)
		component->Update();

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
			delete components[i];
		}
	}

	//Then swap the underlying values
	std::swap(this->components, tmpObjs);
}

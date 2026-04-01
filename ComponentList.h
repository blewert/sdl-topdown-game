#pragma once
#include <vector>

class ComponentList
{
//public:
//	ComponentList() = default;
//	~ComponentList() = default;
//
//	void Add(Component* component);
//
//	
//
//	inline int Count() { return components.size(); };
//
//public:
//	void Update()
//	{
//		for (Component* component : components)
//			component->Update();
//
//		CullPendingDeleteComponents();
//	}
//
//protected:
//	std::vector<Component*> components;
//	
//	void CullPendingDeleteComponents()
//	{
//		std::vector<Component*> tmpObjs;
//
//		for (int i = 0; i < components.size(); i++)
//		{
//			//If not pending delete, add to temp list
//			if (!components[i]->pendingDelete)
//				tmpObjs.push_back(components[i]);
//
//			//Otherwise, call destructor: this will no longer exist
//			//TODO: Call unattach here
//			else delete components[i];
//		}
//
//		//Then swap the underlying values
//		std::swap(this->components, tmpObjs);
//	}
};


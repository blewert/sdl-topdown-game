#pragma once
#include <vector>
#include "Component.h"

class ComponentList
{
public:
	ComponentList() = default;
	~ComponentList() = default;

	void Add(Component* component);

	inline int Count() { return components.size(); };

public:
	void Update();

protected:
	std::vector<Component*> components;
	
	void CullPendingDeleteComponents();
};


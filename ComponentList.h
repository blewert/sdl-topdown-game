#pragma once
#include <vector>
#include <set>
#include "Component.h"

class Rigidbody;

class ComponentList
{
public:
	ComponentList() = default;
	~ComponentList() = default;

	void Add(Component* component);

	inline int Count() { return components.size(); };

public:
	void Update();

	//TODO: Make this nicer, e.g. using a set of types with HasComponent etc
	Rigidbody* rigidbody = nullptr;

protected:
	std::vector<Component*> components;
	
	void CullPendingDeleteComponents();
};


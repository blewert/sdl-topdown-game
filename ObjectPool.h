#pragma once
#include <vector>
#include "GameObject.h"

template <typename T>
union PoolSlot
{
	class ObjectPool;

	T* obj;
	PoolSlot* next;

	void Reset(ObjectPool& parent)
	{
		this->next = parent.firstAvailable;
		parent.firstAvailable = this;
	}
};


template <typename T>
class ObjectPool
{
protected:

	std::vector<PoolSlot<T>> poolData;
	PoolSlot<T>* firstAvailable;

	unsigned int poolSize;

public:
	ObjectPool(int capacity) : poolSize(capacity)
	{
		Allocate(capacity);
	}

	~ObjectPool()
	{
		Deallocate();
	}

	void Deallocate()
	{
		if (poolData.size() <= 0)
			return;

		//Do deallocation here
	}

	void Allocate(int capacity)
	{
		Deallocate();

		poolData = std::vector<PoolSlot<T>>(capacity);

		for (int i = 0; i < capacity - 1; i++)
		{
			poolData[i].next = &poolData[i + 1];
		}

		poolData[capacity - 1].next = nullptr;
		firstAvailable = &poolData[0];
	}

	PoolSlot<T>* Acquire(const T& newVal)
	{
		if (firstAvailable == nullptr)
			return nullptr;

		PoolSlot<T>* slot = firstAvailable;
		firstAvailable = slot->next;

		new (&slot->obj) T(newVal);

		return slot;
	}

	template <typename... Args>
	PoolSlot<T>* Acquire(Args&&... args) 
	{
		if (firstAvailable == nullptr)
			return nullptr;

		PoolSlot<T>* slot = firstAvailable;
		firstAvailable = slot->next;

		new (&slot->obj) T(std::forward<Args>(args)...);

		return slot;
	}

};

ObjectPool<GameObject>* a = new ObjectPool<GameObject>(100);

void ab()
{
	PoolSlot<GameObject>* b = a->Acquire(GameObject(nullptr));
	PoolSlot<GameObject>* c = a->Acquire(nullptr);
}

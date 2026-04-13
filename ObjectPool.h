#pragma once
#include <vector>
#include "GameObject.h"

template<typename T>
class ObjectPool;

template <typename T>
union PoolSlot
{
protected:
	void* obj[sizeof(T)];
	PoolSlot<T>* next;

public:

	T* GetObj()
	{
		return (T*)obj;
	}

	void Reset(ObjectPool<T>& parent)
	{
		this->next = parent.firstAvailable;
		parent.firstAvailable = this;
	}

	friend class ObjectPool<T>;
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
			SDL_Log("This %d, next %d", &poolData[i], poolData[i].next);
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

		new (slot->obj) T(newVal);
		
		return slot;
	}

	template <typename... Args>
	PoolSlot<T>* Acquire(Args&&... args) 
	{
		if (firstAvailable == nullptr)
			return nullptr;

		SDL_Log("Next available is %x", firstAvailable);

		PoolSlot<T>* slot = firstAvailable;
		firstAvailable = slot->next;
		
		SDL_Log("Changed next available is %x", firstAvailable);

		new (slot->obj) T(std::forward<Args>(args)...);

		return slot;
	}

};

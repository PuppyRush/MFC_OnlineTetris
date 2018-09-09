#pragma once

#include <iostream>

#include <queue>
#include <memory>
#include <list>
#include <map>
#include <thread>
#include <mutex>

#include "ITObjectContainer.h"

template <class T>
class TObjectContainer : public ITObjectContainer
{
public:
	
	using PtrType = std::shared_ptr<T>;

	class ContainerIterator
	{
	public:
		T* ptrValue;
		size_t position;

		ContainerIterator()
			:ptrValue(nullptr), position(0)
		{}

		explicit ContainerIterator(T* value, const size_t pos) noexcept
				:ptrValue(value),position(pos)
		{
		}

		T* operator*() { return ptrValue; }
		T* operator->() { return ptrValue;}
		bool operator!=(const ContainerIterator &other)
		{
			if(ptrValue==nullptr || other.ptrValue == nullptr)
				return false;
			else if(position==0 || other.position==0 || position > other.position)
				return false;
			else
				return !(*ptrValue != *(other.ptrValue));
		}
		ContainerIterator operator++() { ++position; return *this; }

	};

	~TObjectContainer() {}

	bool add(const PtrType newObj)
	{
		return ITObjectContainer::add(std::dynamic_pointer_cast<TObject>(newObj));
	}

	void addAll(const std::vector<PtrType> &objAry)
	{
		return ITObjectContainer::addAll(newObj);
	}

	bool remove(PtrType removedObj)
	{
		return ITObjectContainer::remove(newObj);
	}

	PtrType at(const tetris::t_unique unique)
	{
		return std::static_pointer_cast<T>(ITObjectContainer::at(unique));
	}

	//void change(const tetris::t_unique unique, const std::shared_ptr<T> &newObj)
	//{
	//	if (remove(unique))
	//	{
	//		add(unique, newObj);
	//		refresh();
	//	}
	//
	//}

	bool exist(const tetris::t_unique unique) const
	{
		return ITObjectContainer::exist(unique);
	}

	void clear() noexcept
	{
		refresh();
		m_ptrMap.clear();
	}

	ContainerIterator begin() const
	{

		if (m_ptrMap.empty())
			return ContainerIterator(0, 0);
		else
		{
			T* begin = dynamic_cast<T*>(m_ptrMap.begin()->second.get());
			return ContainerIterator(begin, m_ptrMap.size());
		}
	}

	ContainerIterator end() const
	{
		if(m_ptrMap.empty())
			return ContainerIterator(0, 0);
		else
		{
			T* end = dynamic_cast<T*>((--m_ptrMap.end())->second.get());
			return ContainerIterator(end, m_ptrMap.size());
		}
	}

	const ContainerIterator cbegin() const noexcept
	{
		T* begin = m_ptrMap.begin()->second.get();
		return ContainerIterator(begin, m_ptrMap.size());
	}

	const ContainerIterator cend() const noexcept
	{
		return ContainerIterator(0, m_ptrMap.size());
	}

	ContainerType getMap()
	{
		return m_ptrMap;
	}

	inline static auto get(const property_distinguish dist)
	{
		static std::shared_ptr<TObjectContainer> container =
				std::shared_ptr<TObjectContainer>(new TObjectContainer(dist));
		return container;
	}

	virtual void refresh() override
	{
		std::lock_guard<std::mutex> lock(m_refreshMutex);

		m_isRefreshing = true;

		while (!m_addedQ.empty())
		{
			auto obj = m_addedQ.front();
			m_addedQ.pop();
			m_ptrMap.insert(make_pair(obj->getUnique(),obj));
		}

		while (!m_removedQ.empty())
		{
			tetris::t_unique unique = m_removedQ.front();
			m_removedQ.pop();
			m_ptrMap.erase(unique);
		}

		m_isRefreshing = false;
	}

	const bool isRefreshing() const
	{	return m_isRefreshing;	}

private:
	TObjectContainer(const property_distinguish dist)
		: ITObjectContainer(dist)
	{}

	
	std::mutex	m_refreshMutex;
	bool m_isRefreshing;
	
	
};


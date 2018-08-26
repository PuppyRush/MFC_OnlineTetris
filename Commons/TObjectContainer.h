#pragma once

#include <iostream>

#include <queue>
#include <memory>
#include <list>
#include <map>
#include <thread>
#include <mutex>

#include "Uncopyable.h"

template <class UniqueType, class T>
class TObjectContainer : public Uncopyable
{
public:
	using PtrType = std::shared_ptr<T>;
	using MyUniqueType = UniqueType;
	using ContainerType = std::map<UniqueType, PtrType>;

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

	bool add(const UniqueType unique, const PtrType &newObj)
	{
		if (m_ptrMap.count(unique) == 0)
		{
			m_addedQ.push(make_pair(unique, newObj));
			refresh();
			return true;
		}
		else
			return false;
	}

	void addAll(const std::vector< std::pair<UniqueType, PtrType>> &objAry)
	{
		for (const std::pair<UniqueType, PtrType> obj : objAry)
		{
			if (m_ptrMap.count(obj.first) == 0)
				m_addedQ.push(obj);
		}
		refresh();
	}

	bool remove(const UniqueType unique)
	{
		if (m_ptrMap.count(unique) > 0)
		{
			m_removedQ.push(unique);
			refresh();
			return true;
		}
		else
			return false;
	}

	PtrType at(const UniqueType unique)
	{
		if (exist(unique))
			return m_ptrMap.at(unique);
	}

	void change(const UniqueType unique, const std::shared_ptr<T> &newObj)
	{
		if (remove(unique))
		{
			add(unique, unique.newObj);
			refresh();
		}

	}

	bool exist(const UniqueType unique) const
	{
		if (m_ptrMap.count(unique))
			return true;
		else
			return false;
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
			T* begin = m_ptrMap.begin()->second.get();
			return ContainerIterator(begin, m_ptrMap.size());
		}
	}

	ContainerIterator end() const
	{
		if(m_ptrMap.empty())
			return ContainerIterator(0, 0);
		else
		{
			T* end = (--m_ptrMap.end())->second.get();
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

	inline static std::shared_ptr<TObjectContainer> get()
	{
		static std::shared_ptr<TObjectContainer> container = std::shared_ptr<TObjectContainer>(new TObjectContainer());
		return container;
	}

	void refresh()
	{
		std::lock_guard<std::mutex> lock(m_refreshMutex);

		m_isRefreshing = true;

		while (!m_addedQ.empty())
		{
			std::pair<UniqueType, PtrType> obj = m_addedQ.front();
			m_addedQ.pop();
			m_ptrMap.insert(obj);
		}

		while (!m_removedQ.empty())
		{
			UniqueType unique = m_removedQ.front();
			m_removedQ.pop();
			m_ptrMap.erase(unique);
		}

		m_isRefreshing = false;
	}

	const bool isRefreshing() const
	{	return m_isRefreshing;	}

private:
	TObjectContainer() {}

	ContainerType m_ptrMap;
	std::mutex	m_refreshMutex;
	bool m_isRefreshing;
	std::queue<std::pair<UniqueType, PtrType>> m_addedQ;
	std::queue<UniqueType> m_removedQ;
};


#pragma once

#include <unordered_map>

#include "Uncopyable.h"
#include "TType.h"
#include "Entity/TObject.h"

class ITObjectContainer : public Uncopyable
{
public:
	using PtrType = std::shared_ptr<TObject>;
	using ContainerType = std::map<tetris::t_unique, PtrType>;
	using Iterator = ContainerType::iterator;

	inline const property_distinguish getDistinguish() const
	{
		return m_dist;
	}

	virtual void refresh() = 0;

	const size_t size() const noexcept
	{
		return m_ptrMap.size();
	}

	Iterator begin()
	{
		return m_ptrMap.begin();
	}

	Iterator end()
	{
		return m_ptrMap.end();
	}

protected:

	ITObjectContainer(const property_distinguish dist)
		:m_dist(dist) 
	{}


	bool _add(const PtrType newObj)
	{
		if (m_ptrMap.count(newObj->getUnique()) == 0)
		{
			m_ptrMap.insert(make_pair(newObj->getUnique(),newObj));
			return true;
		}
		else
			return false;
	}

	void _addAll(const std::vector<PtrType>& objAry)
	{
		for (const auto obj : objAry)
		{
			if (m_ptrMap.count(obj->getUnique()) == 0)
				m_addedQ.push(obj);
		}
		refresh();
	}

	bool _remove(const PtrType removedObj)
	{
		if (m_ptrMap.count(removedObj->getUnique()) > 0)
		{
			m_removedQ.push(removedObj->getUnique());
			refresh();
			return true;
		}
		else
			return false;
	}

	std::shared_ptr<TObject> _at(const tetris::t_unique unique)
	{
		if (_exist(unique))
			return m_ptrMap.at(unique);
		else
			return nullptr;
	}

	bool _exist(const tetris::t_unique unique) const
	{
		if (m_ptrMap.count(unique))
			return true;
		else
			return false;
	}

	const bool isRefreshing() const
	{	return m_isRefreshing;	}

	const ContainerType  getMap() const noexcept
	{
		return m_ptrMap;
	}


protected:
	std::mutex	m_refreshMutex;
	bool m_isRefreshing;

	std::queue<PtrType> m_addedQ;
	std::queue<tetris::t_unique> m_removedQ;
	ContainerType m_ptrMap;

private:
	property_distinguish m_dist;

};

template <class T>
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

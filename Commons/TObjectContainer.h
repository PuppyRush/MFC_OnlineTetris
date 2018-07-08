#pragma once

#include <queue>
#include <memory>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>

#include "Uncopyable.h"
#include "ITObjectContainer.h"

template <class UniqueType, class T>
class TObjectContainer : public ITObjectContainer, public std::iterator<std::bidirectional_iterator_tag, T>, public Uncopyable
{
public:
	using PtrType = std::shared_ptr<T>;
	using MyUniqueType = UniqueType;

	TObjectContainer()
		:m_canAdded(true),
		m_canRemoved(true)
	{}

	~TObjectContainer() {}

	bool add(const UniqueType unique, const PtrType &newObj)
	{
		if (m_ptrMap.count(unique) == 0)
		{
			m_ptrMap.insert(make_pair(unique, newObj));
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
				m_ptrMap.insert(obj);
		}
	}

	bool remove(const UniqueType unique)
	{
		if (m_ptrMap.count(unique) > 0)
		{
			m_ptrMap.erase(unique);
			return true;
		}
		else
			return false;
	}

	PtrType get(const UniqueType unique)
	{
		if (exist(unique))
			return m_ptrMap.at(unique);
	}

	void change(const UniqueType unique, const std::shared_ptr<T> &newObj)
	{
		if (remove(unique))
			add(unique.newObj);
	}
	
	bool exist(const UniqueType unique)
	{
		if (m_ptrMap.count(unique) > 0)
			return true;
		else
			return false;
	}

	void clear()
	{
		m_ptrMap.clear();
	}

	PtrType begin()
	{
		return *m_ptrMap.begin();
	}

	PtrType end()
	{
		return *m_ptrMap.cend();
	}

	const PtrType cbegin()
	{
		return *m_ptrMap.cbegin();
	}

	const PtrType cend()
	{
		return *m_ptrMap.cend();
	}

	inline static std::shared_ptr<TObjectContainer> get()
	{
		static std::shared_ptr<TObjectContainer> container = std::make_shared<TObjectContainer>();
		return container;
	}

protected:
	
private:
	std::vector<PtrType> m_ptrAry;
	std::unordered_map<UniqueType, PtrType> m_ptrMap;

	//std::queue<pair<UniqueType, PtrType> > m_addQ;
	//std::queue<pair<UniqueType, PtrType> > m_removeQ;
	//bool	m_
	std::mutex	m_mutex;
	std::shared_ptr<std::thread>	m_thread;

	volatile bool m_canAdded;
	volatile bool m_canRemoved;

private:

	void _runContainer()
	{
		const auto runfn = &TObjectContainer::_run;
		m_thread = std::make_shared<std::thread>(runfn, this);
		m_thread->join();
	}

	void _run()
	{
	}

};


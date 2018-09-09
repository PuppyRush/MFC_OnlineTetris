#pragma once

#include <unordered_map>

#include "Uncopyable.h"
#include "TType.h"
#include "Entity/TObject.h"

class ITObjectContainer : public Uncopyable
{
public:

	inline const property_distinguish const getDistinguish()
	{
		return m_dist;
	}

	virtual void refresh() = 0;
	

protected:

	using PtrType = std::shared_ptr<TObject>;
	using ContainerType = std::map<tetris::t_unique, PtrType>;

	ITObjectContainer(const property_distinguish dist)
		:m_dist(dist) 
	{}

	bool add(const PtrType newObj)
	{
		if (m_ptrMap.count(newObj->getUnique()) == 0)
		{
			m_addedQ.push(newObj);
			refresh();
			return true;
		}
		else
			return false;
	}

	void addAll(const std::vector<PtrType>& objAry)
	{
		for (const auto obj : objAry)
		{
			if (m_ptrMap.count(obj->getUnique()) == 0)
				m_addedQ.push(obj);
		}
		refresh();
	}

	bool remove(const PtrType removedObj)
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

	std::shared_ptr<TObject> at(const tetris::t_unique unique)
	{
		if (exist(unique))
			return m_ptrMap.at(unique);
		else
			return nullptr;
	}

	bool exist(const tetris::t_unique unique) const
	{
		if (m_ptrMap.count(unique))
			return true;
		else
			return false;
	}

	std::queue<PtrType> m_addedQ;
	std::queue<tetris::t_unique> m_removedQ;
	ContainerType m_ptrMap;

private:
	property_distinguish m_dist;


};
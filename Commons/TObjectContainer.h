#pragma once

#include <iostream>

#include <queue>
#include <memory>
#include <list>
#include <map>
#include <thread>
#include <mutex>

#include "ITObjectContainer.h"
#include "Entity/TSocket.h"

template <class T>
class TObjectContainer : public ITObjectContainer
{
public:
	
	using PtrType = std::shared_ptr<T>;

	~TObjectContainer() {}

	bool add(const PtrType newObj)
	{
		return ITObjectContainer::_add(std::dynamic_pointer_cast<TObject>(newObj));
	}

	void addAll(const std::vector<PtrType> &objAry)
	{
		return ITObjectContainer::_addAll(objAry);
	}

	bool remove(PtrType removedObj)
	{
		return ITObjectContainer::_remove(removedObj);
	}

	PtrType at(const tetris::t_unique unique)
	{
		return std::static_pointer_cast<T>(ITObjectContainer::_at(unique));
	}

	void change(const PtrType newObj)
	{
		if (remove(newObj->getUnique()))
		{
			add(newObj);
			refresh();
		}
	}

	bool exist(const tetris::t_unique unique) const
	{
		return ITObjectContainer::_exist(unique);
	}

	void clear() noexcept
	{
		refresh();
		m_ptrMap.clear();
	}

	ContainerIterator<T> begin() const
	{

		if (m_ptrMap.empty())
			return ContainerIterator<T>(0, 0);
		else
		{
			T* begin = dynamic_cast<T*>(m_ptrMap.begin()->second.get());
			return ContainerIterator<T>(begin, m_ptrMap.size());
		}
	}

	ContainerIterator<T> end() const
	{
		if(m_ptrMap.empty())
			return ContainerIterator<T>(0, 0);
		else
		{
			T* end = dynamic_cast<T*>((--m_ptrMap.end())->second.get());
			return ContainerIterator<T>(end, m_ptrMap.size());
		}
	}

	const ContainerIterator<T> cbegin() const noexcept
	{
		T* begin = m_ptrMap.begin()->second.get();
		return ContainerIterator<T>(begin, m_ptrMap.size());
	}

	const ContainerIterator<T> cend() const noexcept
	{
		return ContainerIterator<T>(0, m_ptrMap.size());
	}

	inline static auto get()
	{
		static tetris::t_ptr<TObjectContainer> container =
				tetris::t_ptr<TObjectContainer>(new TObjectContainer());
		return container;
	}

	virtual void refresh() override
	{
		//std::lock_guard<std::mutex> lock(m_refreshMutex);

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



private:
	TObjectContainer()
	{}

};


template <>
class TObjectContainer<TetrisSocket> : public ITObjectContainer
{
public:

    using T = TetrisSocket;
	using PtrType = std::shared_ptr<T>;

	~TObjectContainer() {}

	bool add(const PtrType newObj)
	{
		if (m_ptrMap.count(newObj->getSocket()) == 0)
		{
			m_ptrMap.insert(make_pair(newObj->getSocket(), newObj));
			return true;
		}
		else
			return false;
	}

	void addAll(const std::vector<PtrType> &objAry)
	{
		for (const auto obj : objAry)
		{
			if (m_ptrMap.count(obj->getSocket()) == 0)
				m_addedQ.push(obj);
		}
		refresh();
	}

	bool remove(const tetris::t_socket socket)
	{
		if (m_ptrMap.count(socket) > 0)
		{
			m_removedQ.push(socket);
			refresh();
			return true;
		}
	}

	bool remove(const PtrType removedObj)
	{
		if (m_ptrMap.count(removedObj->getSocket()) > 0)
		{
			m_removedQ.push(removedObj->getSocket());
			refresh();
			return true;
		}
	}

	PtrType at(const tetris::t_unique unique)
	{
		if (exist(unique))
			return std::dynamic_pointer_cast<T>(m_ptrMap.at(unique));
		else
			return nullptr;
	}

	void change(const PtrType newObj)
	{
		if (remove(newObj))
		{
			add(newObj);
			refresh();
		}
	}

	bool exist(const tetris::t_unique unique) const
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

	ContainerIterator<T> begin() const
	{
		if (m_ptrMap.empty())
			return ContainerIterator<T>(0, 0);
		else
		{
			T* begin = dynamic_cast<T*>(m_ptrMap.begin()->second.get());
			return ContainerIterator<T>(begin, m_ptrMap.size());
		}
	}

	ContainerIterator<T> end() const
	{
		if(m_ptrMap.empty())
			return ContainerIterator<T>(0, 0);
		else
		{
			T* end = dynamic_cast<T*>((--m_ptrMap.end())->second.get());
			return ContainerIterator<T>(end, m_ptrMap.size());
		}
	}

	/*const ContainerIterator<T> cbegin() const noexcept
	{
		T* begin = m_ptrMap.begin()->second.get();
		return ContainerIterator<T>(begin, m_ptrMap.size());
	}

	const ContainerIterator<T> cend() const noexcept
	{
		return ContainerIterator<T>(0, m_ptrMap.size());
	}
*/
	inline static auto get()
	{
		static std::shared_ptr<TObjectContainer<T>> container =
				std::shared_ptr<TObjectContainer<T>>(new TObjectContainer<T>());
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
			auto socket = std::dynamic_pointer_cast<T>(obj);
			m_ptrMap.insert(make_pair(socket->getSocket(),obj));
		}

		while (!m_removedQ.empty())
		{
			tetris::t_unique unique = m_removedQ.front();
			m_removedQ.pop();
			m_ptrMap.erase(unique);
		}

		m_isRefreshing = false;
	}



private:
	TObjectContainer()
	{}

};

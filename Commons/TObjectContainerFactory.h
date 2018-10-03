#pragma once

#include <memory>
#include <unordered_map>

#include "TypeTraits.h"
#include "TType.h"
#include "Uncopyable.h"
#include "TObjectContainer.h"
#include "ITObjectContainer.h"
#include "TProperty.h"
#include "Entity/TUser.h"
#include "Entity/TSocket.h"
#include "Entity/Room/TIGameRoom.h"
#include "Entity/Room/TIWaitingRoom.h"

class TObjectContainerFactory : public Uncopyable
{
public:

	~TObjectContainerFactory() {}

	template <class T>
	using Container = TObjectContainer<T>;



	static inline std::shared_ptr<TObjectContainerFactory> get()
	{
		static std::shared_ptr<TObjectContainerFactory> factory = std::shared_ptr<TObjectContainerFactory>(new TObjectContainerFactory());
		return factory;
	}

	template <class T>
	auto getContainer(const property_distinguish dist)
	{
		const auto _dist = toUType(dist);
		if (m_objMap.count(_dist))
			return std::dynamic_pointer_cast< Container<T>>(m_objMap.at(_dist));
		else
		{
			assert("there is no container");
			return  std::dynamic_pointer_cast<Container<T>>(std::shared_ptr<ITObjectContainer>(nullptr));
		}
	}

private:
	TObjectContainerFactory() 
	{
		auto it = EnumIterator<property_distinguish>();
		for (it.begin() ; it.end() ; ++it)
		{
			auto dist = it.value;
			switch (dist)
			{
			case property_distinguish::GameRoom:
				m_objMap.insert(make_pair( toUType(dist), std::dynamic_pointer_cast<ITObjectContainer>(Container<TIGameRoom>::get(dist))));
				break;
			case property_distinguish::WaitingRoom:
				m_objMap.insert(make_pair(toUType(dist), std::dynamic_pointer_cast<ITObjectContainer>(Container<TIWaitingRoom>::get(dist))));
				break;
			case property_distinguish::User:
				m_objMap.insert(make_pair(toUType(dist), std::dynamic_pointer_cast<ITObjectContainer>(Container<TetrisUser>::get(dist))));
				break;
			case property_distinguish::Socket:
				m_objMap.insert(make_pair(toUType(dist), std::dynamic_pointer_cast<ITObjectContainer>(Container<TetrisSocket>::get(dist))));
				break;
			default:
				assert("make container of registed enum");
			}
		}
	}


	std::unordered_map<tetris::t_dist, std::shared_ptr<ITObjectContainer>> m_objMap;
};

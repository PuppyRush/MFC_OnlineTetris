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
	constexpr auto getContainer()
	{
		return _getCotainer(typename T::dist());
	}

private:
	//TObjectContainerFactory() 
	//{
	//	auto it = EnumIterator<property_distinguish>();
	//	for (it.begin() ; it.end() ; ++it)
	//	{
	//		auto dist = it.value;
	//		switch (dist)
	//		{
	//		case property_distinguish::GameRoom:
	//			m_objMap.insert(make_pair( toUType(dist), std::dynamic_pointer_cast<ITObjectContainer>(Container<TIGameRoom>::get(dist))));
	//			break;
	//		case property_distinguish::WaitingRoom:
	//			m_objMap.insert(make_pair(toUType(dist), std::dynamic_pointer_cast<ITObjectContainer>(Container<TIWaitingRoom>::get(dist))));
	//			break;
	//		case property_distinguish::User:
	//			m_objMap.insert(make_pair(toUType(dist), std::dynamic_pointer_cast<ITObjectContainer>(Container<TetrisUser>::get(dist))));
	//			break;
	//		//case property_distinguish::Socket:
	//			//m_objMap.insert(make_pair(toUType(dist), std::dynamic_pointer_cast<ITObjectContainer>(Container<TetrisSocket>::get(dist))));
	//			break;
	//		default:
	//			assert("make container of registed enum");
	//		}
	//	}
	//}

	auto _getCotainer(distinguishType<TetrisUser>)
	{
		static auto container = TObjectContainer<TetrisUser>::get();
		return container;
	}

	auto _getCotainer(distinguishType<TIWaitingRoom>)
	{
		static auto container = TObjectContainer<TIWaitingRoom>::get();
		return container;
	}

	auto _getCotainer(distinguishType<TIGameRoom>)
	{
		static auto container = TObjectContainer<TIGameRoom>::get();
		return container;
	}

	auto _getCotainer(distinguishType<TetrisSocket>)
	{
		static auto container = TObjectContainer<TetrisSocket>::get();
		return container;
	}

	std::unordered_map<tetris::t_dist, std::shared_ptr<ITObjectContainer>> m_objMap;
};

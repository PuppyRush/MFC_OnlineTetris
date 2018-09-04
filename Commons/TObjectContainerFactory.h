#pragma once

#include <memory>

#include "TType.h"
#include "Uncopyable.h"
#include "TObjectContainer.h"
#include "TUser.h"
#include "TSocket.h"
#include "Room/TIGameRoom.h"
#include "Room/TIWaitingRoom.h"
#include "TProperty.h"

class TObjectContainerFactory : public Uncopyable
{
public:

	template <class T>
	using Container = TObjectContainer<T>;

	static inline std::shared_ptr<TObjectContainerFactory> get()
	{
		static std::shared_ptr<TObjectContainerFactory> factory = std::shared_ptr<TObjectContainerFactory>(new TObjectContainerFactory());
		return factory;
	}

	auto getUserContainer()
	{
		return Container<TetrisUser>::get(toUType(property_distinguish::User));
	}

	auto getSocketContainer()
	{
		return Container<TetrisSocket>::get(toUType(property_distinguish::Socket));
	}

	auto getGameRoomContainer()
	{
		return Container<TIGameRoom>::get(toUType(property_distinguish::GameRoom));
	}

	auto getWaitingRoomContainer()
	{
		return Container<TIWaitingRoom>::get(toUType(property_distinguish::WaitingRoom));
	}

private:
	TObjectContainerFactory() {}
};

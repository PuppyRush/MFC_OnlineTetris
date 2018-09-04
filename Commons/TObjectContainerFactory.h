#pragma once

#include <memory>

#include "TType.h"
#include "Uncopyable.h"
#include "TObjectContainer.h"
#include "Entity/TUser.h"
#include "Entity/TSocket.h"
#include "Entity/Room/TIGameRoom.h"
#include "Entity/Room/TIWaitingRoom.h"

class TObjectContainerFactory : public Uncopyable
{
public:

	template <class U, class T>
	using Container = TObjectContainer<U, T>;

	static inline std::shared_ptr<TObjectContainerFactory> get()
	{
		static std::shared_ptr<TObjectContainerFactory> factory = std::shared_ptr<TObjectContainerFactory>(new TObjectContainerFactory());
		return factory;
	}

	std::shared_ptr<Container<tetris::t_userUnique, TetrisUser>> getUserContainer()
	{
		return Container<tetris::t_userUnique, TetrisUser>::get();
	}

	std::shared_ptr<Container<tetris::t_socketUnique, TetrisSocket>> getSocketContainer()
	{
		return Container<tetris::t_socketUnique, TetrisSocket>::get();
	}

	std::shared_ptr<Container<tetris::t_roomUnique, TIGameRoom>> getGameRoomContainer()
	{
		return Container<tetris::t_roomUnique, TIGameRoom>::get();
	}

	std::shared_ptr<Container<tetris::t_roomUnique, TIWaitingRoom>> getWaitingRoomContainer()
	{
		return Container<tetris::t_roomUnique, TIWaitingRoom>::get();
	}

private:
	TObjectContainerFactory() {}
};

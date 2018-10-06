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

#define USER_CON() TObjectContainerFactory::get()->getContainer<TetrisUser>();

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
	auto getContainer()
	{
		static auto container = TObjectContainer<T>::get();
		return container; 
	}

private:
	TObjectContainerFactory() = default;

	std::unordered_map<tetris::t_dist, std::shared_ptr<ITObjectContainer>> m_objMap;
};

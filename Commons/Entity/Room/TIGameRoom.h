/*
 * TGameRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_map>
#include <mutex>

#include "TIRoom.h"
#include "../../TType.h"
#include "../../TAtomic.h"

class TIGameRoom : public TIRoom
{
public:
	using dist = distinguishType<TIGameRoom>;

	enum class property : tetris::t_property
	{
		MinimunCount = 2,
		MaxCount = 8,
	};

	virtual ~TIGameRoom() {}


protected:
	TIGameRoom() {}
	explicit TIGameRoom(const RoomInfo& roominfo);

};

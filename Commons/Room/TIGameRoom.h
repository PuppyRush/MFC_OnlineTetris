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
#include "../TType.h"
#include "../TAtomic.h"
#include "../TSwitchingMessage.h"

class TIGameRoom : public TIRoom
{
public:
	TIGameRoom() {}
	virtual ~TIGameRoom() {}

	virtual const tetris::t_error insertRoom(std::shared_ptr<TIGameRoom> room) = 0;
	virtual const tetris::t_error switchingMessage(const tetris::msgElement &msg) = 0;

	inline bool operator!=(const TIGameRoom& room)
	{	return	getUnique() != room.getUnique();	}

protected:
	std::unordered_map< tetris::t_roomUnique, std::shared_ptr<TIGameRoom>> m_roomMap;

};

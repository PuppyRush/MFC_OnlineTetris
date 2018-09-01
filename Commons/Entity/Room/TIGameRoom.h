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
#include "../TMessenger.h"

class TIGameRoom : public TIRoom
{
public:
	virtual ~TIGameRoom() {}

	inline bool operator!=(const TIGameRoom& room)
	{	return	getUnique() != room.getUnique();	}

protected:
	TIGameRoom(const tetris::t_roomUnique ,const std::string roomname);


	std::unordered_map< tetris::t_roomUnique, std::shared_ptr<TIGameRoom>> m_roomMap;

};

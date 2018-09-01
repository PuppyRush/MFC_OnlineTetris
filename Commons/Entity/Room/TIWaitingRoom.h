/*
 * TWaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_set>
#include <memory>

#include "../../Commons/Entity/Room/TIRoom.h"
#include "../../Commons/Entity/TUser.h"
#include "../../Commons/TMessenger.h"


class TIWaitingRoom : public TIRoom
{
public:
	virtual ~TIWaitingRoom() {}

	inline const bool operator!=(const TIWaitingRoom& room) const
	{
		return	getUnique() != room.getUnique();
	}

	virtual const tetris::t_error addRoom(const tetris::t_roomUnique roomUnique);
	virtual const tetris::t_error exitRoom(const tetris::t_roomUnique roomUnique);
	virtual const tetris::t_error existRoom(const tetris::t_roomUnique roomUnique);

protected:

	TIWaitingRoom(const tetris::t_roomUnique unique, std::string nameroom);

	std::unordered_set< tetris::t_roomUnique> m_roomSet;
};

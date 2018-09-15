/*
 * TWaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_set>
#include <memory>

#include "TIRoom.h"
#include "../TUser.h"


class TIWaitingRoom : public TIRoom
{
public:
	virtual ~TIWaitingRoom() {}

	virtual const tetris::t_error addRoom(const tetris::t_unique roomUnique);
	virtual const tetris::t_error exitRoom(const tetris::t_unique roomUnique);
	virtual const tetris::t_error existRoom(const tetris::t_unique roomUnique);

protected:
	TIWaitingRoom() {}
	explicit TIWaitingRoom(const std::shared_ptr<RoomInfo> roominfo, const std::vector<UserInfo>& userinfoAry);

	std::unordered_set< tetris::t_unique> m_roomSet;
};

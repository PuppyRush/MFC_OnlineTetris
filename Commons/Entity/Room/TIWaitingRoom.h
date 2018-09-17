/*
 * TWaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_set>
#include <memory>

#include "../../structs.h"
#include "TIRoom.h"
#include "../TUser.h"


class TIWaitingRoom : public TIRoom
{
public:
	virtual ~TIWaitingRoom() {}

	virtual const tetris::t_error addRoom(const tetris::t_ptr<RoomInfo> roomUnique);
	virtual const tetris::t_error exitRoom(const tetris::t_unique roomUnique);
	virtual const tetris::t_error existRoom(const tetris::t_unique roomUnique);

	const std::shared_ptr<std::vector<roomInfo>> getWaitingRoomsInfo() const;

protected:
	TIWaitingRoom() {}
	explicit TIWaitingRoom(const std::shared_ptr<RoomInfo> roominfo, const std::vector<UserInfo>& userinfoAry);

	std::unordered_map<tetris::t_unique, tetris::t_ptr<RoomInfo>> m_roomSet;
};

/*
 * TWaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_map>
#include <memory>

#include "../../structs.h"
#include "TIRoom.h"
#include "../TUser.h"


class TIWaitingRoom : public TIRoom
{
public:
	using dist = distinguishType<TIWaitingRoom>;

	virtual ~TIWaitingRoom() {}

	tetris::t_error addGameRoom(const RoomInfo& roominfo, const UserInfo& master);
	tetris::t_error removeGameRoom(const tetris::t_unique);

	static const std::shared_ptr<std::vector<RoomInfo>> getWaitingRoomsInfo();

protected:
	std::unordered_map<tetris::t_unique, tetris::t_ptr<RoomInfo>> m_roommap;

	TIWaitingRoom();
	explicit TIWaitingRoom(const RoomInfo& roominfo);

private:

};

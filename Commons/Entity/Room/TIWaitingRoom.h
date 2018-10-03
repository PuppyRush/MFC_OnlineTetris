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

	tetris::t_error addGameRoom(const RoomInfo&);
	tetris::t_error removeGameRoom(const tetris::t_unique);
	virtual const tetris::t_error enter(const UserInfo &userinfo) override;
	virtual const tetris::t_error enter(const TetrisUser &userinfo) override;
	virtual const tetris::t_error exit(const tetris::t_unique user) override;

	static const std::shared_ptr<std::vector<RoomInfo>> getWaitingRoomsInfo();

protected:
	std::unordered_map<tetris::t_unique, tetris::t_ptr<RoomInfo>> m_roommap;

	TIWaitingRoom() {}
	explicit TIWaitingRoom(const RoomInfo& roominfo);

private:

};

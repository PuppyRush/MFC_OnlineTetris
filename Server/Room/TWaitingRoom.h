/*
 * TWaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_set>
#include <memory>

#include "../../Commons/Entity/Room/TIWaitingRoom.h"
#include "../../Commons/Entity/TUser.h"


class TWaitingRoom : public TIWaitingRoom
{
public:

	virtual ~TWaitingRoom();

	enum class property : tetris::t_error
	{
		Size = 200
	};

	virtual void registryMessage() override;
	virtual const tetris::t_error _validator(const TIRoom &room) const override;

	void sendWaitingUsers(const tetris::t_socket socketUnique);
	void sendWaitingRooms(const tetris::t_socket socketUnique);

	static tetris::t_ptr<TWaitingRoom> makeShared(const RoomInfo& room)
	{
		return tetris::t_ptr<TWaitingRoom>(new TWaitingRoom(room));
	}

private:
	explicit TWaitingRoom(const RoomInfo& roominfo);

};

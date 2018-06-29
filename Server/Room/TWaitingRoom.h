/*
 * TWaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include "TRoom.h"
#include "../Server/TServerUser.h"

class TWaitingRoom : public TRoom
{
public:

	enum class property : std::uint16_t
	{
		Size = 200
	};

	TWaitingRoom() {}
	explicit TWaitingRoom(const string roomname, const std::vector<shared_ptr<TServerUser>> userQ);
	virtual ~TWaitingRoom();

	inline static shared_ptr<TWaitingRoom> getWaitingRoom()
	{
		static auto waitingRoom = make_shared<TWaitingRoom>();
		return waitingRoom;
	}

};

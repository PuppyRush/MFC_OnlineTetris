/*
 * TWaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_set>

#include "TRoom.h"
#include "../Server/TServerUser.h"

class TWaitingRoom : public TRoom
{
public:
	virtual ~TWaitingRoom();

	enum class property : tetris::t_error
	{
		Size = 200
	};

	inline static shared_ptr<TWaitingRoom> getWaitingRoom()
	{
		static auto waitingRoom = shared_ptr<TWaitingRoom>(new TWaitingRoom());
		return waitingRoom;
	}

	const errorCode insertRoom(const TRoom &room);
	const errorCode validator(const TRoom &room) const;

protected:

private:
	
};

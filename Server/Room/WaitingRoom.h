/*
 * WaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include "Room.h"
#include "../Server/TServerUser.h"


class WaitingRoom : public Room
{
public:
	explicit WaitingRoom(const string roomname, const list<shared_ptr<TServerUser>> userQ);

	inline  static shared_ptr<WaitingRoom> getWaitingRoom(const string roomname, const list<shared_ptr<TServerUser>> userQ)
	{
		return m_waitingRoom;
	}

protected:

	WaitingRoom();
	virtual ~WaitingRoom();

private:
	static shared_ptr<WaitingRoom> m_waitingRoom;
};

/*
 * GameRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include "Room.h"

class GameRoom : public TRoom
{
private:

	explicit GameRoom(const string roomname, const list<shared_ptr<TServerUser>> userQ);
	virtual ~GameRoom();

public:

};

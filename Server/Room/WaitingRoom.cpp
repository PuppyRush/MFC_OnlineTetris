/*
 * WaitingRoom.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include "WaitingRoom.h"

WaitingRoom::WaitingRoom(const string roomname, const list<shared_ptr<TServerUser>> userQ)
	:Room(roomname,userQ)
{
	// TODO Auto-generated constructor stub

}

WaitingRoom::~WaitingRoom()
{
	// TODO Auto-generated destructor stub
}


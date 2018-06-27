/*
 * GameRoom.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include "GameRoom.h"

GameRoom::GameRoom(const string roomname, const list<shared_ptr<TServerUser>> userQ)
	:Room(roomname,userQ)
{
	// TODO Auto-generated constructor stub

}

GameRoom::~GameRoom()
{
	// TODO Auto-generated destructor stub
}

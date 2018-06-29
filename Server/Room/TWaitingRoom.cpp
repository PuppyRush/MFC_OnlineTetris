/*
 * TWaitingRoom.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <ctime>

#include "../../Commons/Validator.h"
#include "TWaitingRoom.h"

TWaitingRoom::TWaitingRoom(const string roomname, const vector<shared_ptr<TServerUser>> userQ)
	:TRoom(roomname,userQ)
{
	// TODO Auto-generated constructor stub

}

TWaitingRoom::~TWaitingRoom()
{
	// TODO Auto-generated destructor stub
}

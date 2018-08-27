/*
 * TWaitingRoom.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <ctime>

#include "../../Commons/Validator.h"
#include "TWaitingRoom.h"
#include "../../Commons/TypeTraits.h"

TWaitingRoom::TWaitingRoom(const tetris::t_roomUnique roomUnique)
:TIWaitingRoom(roomUnique, std::string("ServerWaitingRoom"))
{
    registryMessage();
}

TWaitingRoom::~TWaitingRoom()
{
	// TODO Auto-generated destructor stub
}

void TWaitingRoom::registryMessage()
{

}

const tetris::t_error TWaitingRoom::_validator(const TIRoom &room) const
{
	//const auto roominfo = room.getRoomInfo();
	//const auto roomname = roominfo->roomName;
	//if (!stringLengthCheck(roominfo->roomName, toUType(property::LengthMin), toUType(property::LengthMin)))
	//	return errorCode::NameLength;
	//
	//for (const auto _room : m_roomMap)
	//{
	//	if (_room.second->getRoomInfo()->roomName.compare(roomname) == 0)
	//		return errorCode::NameLength;
	//}
	//
	//const auto currentTime = time(NULL);
	//if (std::difftime(currentTime, roominfo->makeTime) < 0)
	//	return errorCode::PassedTime;
	//
	////if(roominfo->users.empty())
	////	return errorCode::Nobody;
	//
	//return errorCode::Ok;
}
/*
 * TWaitingRoom.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <ctime>

#include "../../Commons/Validator.h"
#include "TWaitingRoom.h"

//TWaitingRoom::TWaitingRoom(const string roomname, const vector<shared_ptr<TServerUser>> userQ)
//	:TRoom(roomname,userQ)
//{
//	// TODO Auto-generated constructor stub
//
//}

TWaitingRoom::~TWaitingRoom()
{
	// TODO Auto-generated destructor stub
}


//const TWaitingRoom::errorCode TWaitingRoom::insertRoom(const TRoom &room)
//{
//	const auto errCode = validator(room);
//	if (errCode == errorCode::Ok)
//		getWaitingRoom()->m_roomMap.insert.make_pair(m_unique.newUnique(), room);
//	else
//		return errCode;
//}
//
//const TWaitingRoom::errorCode TWaitingRoom::validator(const TRoom &room) const
//{
//	const auto roominfo = room.getRoomInfo();
//	const auto roomname = roominfo->roomName;
//	if (!stringLengthCheck(roominfo->roomName, toUType(property::LengthMin), toUType(property::LengthMin)))
//		return errorCode::NameLength;
//
//	for (const auto _room : m_roomMap)
//	{
//		if (_room.second->getRoomInfo()->roomName.compare(roomname) == 0)
//			return errorCode::NameLength;
//	}
//
//	const auto currentTime = time(NULL);
//	if (std::difftime(currentTime, roominfo->makeTime) < 0)
//		return errorCode::PassedTime;
//
//	//if(roominfo->users.empty())
//	//	return errorCode::Nobody;
//
//	return errorCode::Ok;
//}
/*
 * TGameRoom.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <ctime>

#include "TGameRoom.h"
#include "../../Commons/Validator.h"
#include "../../Commons/TypeTraits.h"

using namespace std;

TGameRoom::TGameRoom(const string roomname, const vector<shared_ptr<TServerUser>> userQ)
	:TRoom(roomname,userQ)
{
	// TODO Auto-generated constructor stub

}

TGameRoom::~TGameRoom()
{
	// TODO Auto-generated destructor stub
	m_roomMap.clear();
}



const TGameRoom::errorCode TGameRoom::insertRoom(shared_ptr<TGameRoom> room)
{
	const auto errCode = _validator(*room.get());
	if (errCode == errorCode::Ok)
		getRameRoom()->m_roomMap.insert(make_pair(m_unique.newUnique(), room));

	return errCode;
}

const TGameRoom::errorCode TGameRoom::_validator(const TRoom &room) const
{
	const auto roominfo = room.getRoomInfo();
	const auto roomname = roominfo->roomName;
	if (!stringLengthCheck(roominfo->roomName, toUType(TRoom::property::LengthMin), toUType(TRoom::property::LengthMin)))
		return errorCode::NameLength;

	for (const auto _room : m_roomMap)
	{
		if (_room.second->getRoomInfo()->roomName.compare(roomname) == 0)
			return errorCode::NameLength;
	}

	const auto currentTime = time(NULL);
	if (std::difftime(currentTime, roominfo->makeTime) < 0)
		return errorCode::PassedTime;

	return errorCode::Ok;
}
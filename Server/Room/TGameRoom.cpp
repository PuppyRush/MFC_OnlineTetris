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

TGameRoom::TGameRoom(const tetris::t_roomUnique roomUnique, const string roomname)
:TIGameRoom(roomUnique,roomname)
{
	// TODO Auto-generated constructor stub

}

TGameRoom::~TGameRoom()
{
	// TODO Auto-generated destructor stub
	m_roomMap.clear();
}

const tetris::t_error TGameRoom::registryMessage()
{

}

const tetris::t_error TGameRoom::_validator(const TIRoom &room) const
{
	const auto roominfo = room.getRoomInfo();
	const auto roomname = roominfo->roomName;
	if (!stringLengthCheck(roominfo->roomName, toUType(TIRoom::property::LengthMin), toUType(TIRoom::property::LengthMin)))
		return toUType(errorCode::OverNameLength);

	for (const auto _room : m_roomMap)
	{
		if (_room.second->getRoomInfo()->roomName.compare(roomname) == 0)
			return toUType(errorCode::OverNameLength);
	}

	const auto currentTime = time(NULL);
	if (std::difftime(currentTime, roominfo->makeTime) < 0)
		return toUType(errorCode::PassedTime);

	return toUType(errorCode::Ok);
}
/*
 * TGameRoom.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <ctime>
#include <string.h>

#include "TGameRoom.h"
#include "../../Commons/Validator.h"
#include "../../Commons/TypeTraits.h"
#include "../../Commons/TObjectContainerFactory.h"

using namespace std;

TGameRoom::TGameRoom( const RoomInfo& roominfo)
:TIGameRoom(roominfo)
{
	// TODO Auto-generated constructor stub
	registryMessage();
}

TGameRoom::~TGameRoom()
{
	// TODO Auto-generated destructor stub
	m_roomMap.clear();
}

void TGameRoom::registryMessage()
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
		if (strcmp(_room.second->getRoomInfo()->roomName, roomname) == 0)
			return toUType(errorCode::OverNameLength);
	}

	const auto currentTime = time(NULL);
	if (std::difftime(currentTime, roominfo->makeTime) < 0)
		return toUType(errorCode::PassedTime);

	return toUType(errorCode::Ok);
}

bool TGameRoom::makeGameRoom(const RoomInfo& room)
{
	auto newroom = makeShared(room);
	TObjectContainerFactory::get()->getContainer<TIGameRoom>()->add(newroom);
}
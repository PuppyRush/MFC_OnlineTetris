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

TGameRoom::TGameRoom(const string roomname)
{
	// TODO Auto-generated constructor stub

}

TGameRoom::~TGameRoom()
{
	// TODO Auto-generated destructor stub
	m_roomMap.clear();
}

const tetris::t_error TGameRoom::switchingMessage(const tetris::msgElement &msg)
{

}

const TIRoom::errorCode TGameRoom::add(const shared_ptr<TetrisUser> user)
{
	if (m_userSet.count(user) == 0)
	{
		m_userSet.insert(user);
		return TIRoom::errorCode::Ok;
	}
	else
		return TIRoom::errorCode::Exist;
}

const TIRoom::errorCode TGameRoom::exit(const shared_ptr<TetrisUser> user)
{
	if (m_userSet.count(user) > 0)
	{
		m_userSet.erase(user);
		return TIRoom::errorCode::Ok;
	}
	else
		return TIRoom::errorCode::Empty;
}


const tetris::t_error TGameRoom::insertRoom(std::shared_ptr<TIGameRoom> room)
{
	
	const auto errCode = _validator(*room.get());
	if (errCode == toUType(TGameRoom::errorCode::Ok))
		getRameRoom()->m_roomMap.insert(make_pair(m_unique.newUnique(), room));

	return errCode;
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
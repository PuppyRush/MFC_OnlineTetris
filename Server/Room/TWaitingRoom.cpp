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


const tetris::t_error TWaitingRoom::switchingMessage(const tetris::msgElement &msg)
{

}

const TIRoom::errorCode TWaitingRoom::add(const std::shared_ptr<TetrisUser> user)
{
	if (m_userSet.count(user) == 0)
	{
		m_userSet.insert(user);
		return TIRoom::errorCode::Ok;
	}
	else
		return TIRoom::errorCode::Exist;
}

const TIRoom::errorCode TWaitingRoom::exit(const std::shared_ptr<TetrisUser> user)
{
	if (m_userSet.count(user) > 0)
	{
		m_userSet.erase(user);
		return TIRoom::errorCode::Ok;
	}
	else
		return TIRoom::errorCode::Empty;
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
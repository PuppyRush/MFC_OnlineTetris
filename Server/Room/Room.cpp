/*
 * TRoom.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include "Room.h"
#include "../Server/TServerUser.h"

TRoom::TRoom(const std::string roomname, const std::list<shared_ptr<TServerUser>> userQ)
{
	gmtime(&m_roominfo.makeTime);
	for (const auto user : userQ)
	{
		addUser(user);
	}
}

TRoom::~TRoom()
{
	// TODO Auto-generated destructor stub
}

const bool TRoom::addUser(shared_ptr<TServerUser> user)
{
	if (m_roominfo.users.count(user->getUnique()) > 0)
	{
		//logger
	}
	else
		m_roominfo.users.insert(make_pair(user->getUnique(), user));
}

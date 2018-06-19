/*
 * Room.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include "Room.h"
#include "../Server/TServerUser.h"

typedef struct Room::pImp
{
public:
	tetris::t_roomUnique m_unique;
	time_t m_makeTime;
	string m_roomName;
	map<tetris::t_unique, shared_ptr<TServerUser>> m_users;

	pImp() = default;
};

Room::Room(const string roomname, const list<shared_ptr<TServerUser>> userQ)
	:m_pImp(make_shared<pImp>())
{
	gmtime(&m_pImp->m_makeTime);
	for (const auto user : userQ)
	{
		addUser(user);
	}
}

Room::~Room()
{
	// TODO Auto-generated destructor stub
}

const bool Room::addUser(shared_ptr<TServerUser> user)
{
	if (m_pImp->m_users.count(user->getUnique()) > 0)
	{
		//logger
	}
	else
		m_pImp->m_users.insert(make_pair(user->getUnique(), user));
}

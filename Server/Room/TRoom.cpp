/*
 * TRoom.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include "TRoom.h"
#include "../Server/TServerUser.h"

TRoom::TRoom(const std::string roomname, const std::vector<shared_ptr<TServerUser>> userQ)
	:m_unique(getAtomic().newUnique())
{
	gmtime(&m_roominfo->makeTime);
	for (const auto user : userQ)
	{
		add(user);
	}
}

TRoom::~TRoom()
{
	// TODO Auto-generated destructor stub
}

const TRoom::errorCode TRoom::add(const shared_ptr<TServerUser> user)
{
	if ( m_userSet.count(user) == 0)
	{
		m_userSet.insert(user);
		return errorCode::Ok;
	}
	else
		return errorCode::Exist;
}

const TRoom::errorCode TRoom::exit(const shared_ptr<TServerUser> user)
{
	if (m_userSet.count(user) > 0)
	{
		m_userSet.erase(user);
		return errorCode::Ok;
	}
	else
		return errorCode::Empty;
}

const vector<userInfo> TRoom::getUserInfo() const
{
	vector<UserInfo> userinfoAry;
	userinfoAry.reserve(m_userSet.size());
	for (const auto user : m_userSet)
	{
		UserInfo info(user->getUnique(), user->getUserName());
		userinfoAry.emplace_back(info);
	}

	return userinfoAry;
}
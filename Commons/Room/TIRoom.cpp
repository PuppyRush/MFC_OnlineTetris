/*
 * TRoom.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include "TIRoom.h"
#include "../TUser.h"

using namespace std;

TIRoom::TIRoom(const std::string roomname)
	:m_unique(TIRoom::getAtomic())
{
	gmtime(&m_roominfo->makeTime);
}

TIRoom::~TIRoom()
{
	// TODO Auto-generated destructor stub
}

const vector<userInfo> TIRoom::getUserInfo() const
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
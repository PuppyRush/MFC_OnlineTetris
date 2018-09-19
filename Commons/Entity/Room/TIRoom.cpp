/*
 * TRoom.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include "TIRoom.h"
#include "../TUser.h"

#include <stdint.h>
#include <ctime>

#include "../../TObjectContainerFactory.h"

using namespace std;

TIRoom::TIRoom(const RoomInfo& roominfo)
{
	m_roomInfo = make_shared<RoomInfo>(roominfo);
	m_roomInfo->unique = this->getUnique();
	m_roomInfo->makeTime =  std::time(0);
	auto l = sizeof(RoomInfo); //40
	if(l==8)
		l++;
}

TIRoom::~TIRoom()
{
	// TODO Auto-generated destructor stub
}

const tetris::t_error TIRoom::add(const tetris::t_ptr<UserInfo> userinfo)
{
	if (m_userInfo.count(userinfo->userUnique) == 0)
	{
		m_userInfo.insert(make_pair(userinfo->userUnique, userinfo));
		return toUType( TIRoom::errorCode::Ok);
	}
	else
		return toUType(TIRoom::errorCode::Exist);
}

const tetris::t_error TIRoom::exit(const tetris::t_unique user)
{
	if (m_userInfo.count(user) > 0)
	{
		m_userInfo.erase(user);
		return toUType(TIRoom::errorCode::Ok);
	}
	else
		return toUType(TIRoom::errorCode::Empty);
}

const bool TIRoom::exist(const tetris::t_unique user) const
{
	if (m_userInfo.count(user))
		return true;
	else
		return false;
}

const shared_ptr<vector<UserInfo>> TIRoom::getUserInfo() const
{
	auto userinfoAry = make_shared<vector<UserInfo>>();
	userinfoAry->reserve(m_userInfo.size());
	auto userCon = TObjectContainerFactory::get()->getContainer<TetrisUser>(property_distinguish::User);

	for (const auto user : m_userInfo)
	{
		if(userCon->exist(user.first))
		{
			UserInfo info(user.first, userCon->at(user.first)->getUserName().c_str());
			userinfoAry->emplace_back(info);
		}
	}

	return userinfoAry;
}

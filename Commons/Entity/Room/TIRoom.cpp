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

TIRoom::TIRoom(const std::shared_ptr<RoomInfo> roominfo, const std::vector<UserInfo>& userinfoAry)
	:m_roomInfo(roominfo)
	//m_userCon(TObjectContainerFactory::get()->getContainer<TetrisUser>(property_distinguish::User))
{
	m_userInfo.reserve(userinfoAry.size());
	for (auto info : userinfoAry)
	{
		auto userinfo = std::make_shared<UserInfo>(info.userUnique, string(info.name));
		m_userInfo.insert(make_pair(info.userUnique, userinfo));
	}
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

const vector<UserInfo> TIRoom::getUserInfo() const
{
	vector<UserInfo> userinfoAry;
	userinfoAry.reserve(m_userInfo.size());
	auto userCon = TObjectContainerFactory::get()->getContainer<TetrisUser>(property_distinguish::User);

	for (const auto user : m_userInfo)
	{
		if(userCon->exist(user.first))
		{
			UserInfo info(user.first, userCon->at(user.first)->getUserName());
			userinfoAry.emplace_back(info);
		}
	}

	return userinfoAry;
}

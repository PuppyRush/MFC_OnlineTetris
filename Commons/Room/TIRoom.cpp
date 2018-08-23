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

#include "../TObjectContainerFactory.h"

using namespace std;

TIRoom::TIRoom(const tetris::t_roomUnique roomuUnique ,const std::string roomname)
	:m_unique(roomuUnique),
	m_roomname(roomname)
{

	time_t ltime = 0;
	std::time(&ltime);

	//m_roominfo->makeTime = ltime;
}

TIRoom::~TIRoom()
{
	// TODO Auto-generated destructor stub
}

const size_t TIRoom::size() const
{
	return m_userSet.size();
}

const tetris::t_error TIRoom::add(const tetris::t_userUnique unique)
{
	if (m_userSet.count(unique) == 0)
	{
		m_userSet.insert(unique);
		return toUType( TIRoom::errorCode::Ok);
	}
	else
		return toUType(TIRoom::errorCode::Exist);
}

const tetris::t_error TIRoom::exit(const tetris::t_userUnique unique)
{
	if (m_userSet.count(unique) > 0)
	{
		m_userSet.erase(unique);
		return toUType(TIRoom::errorCode::Ok);
	}
	else
		return toUType(TIRoom::errorCode::Empty);
}

const bool TIRoom::exist(const tetris::t_userUnique unique) const
{
	if (m_userSet.count(unique))
		return true;
	else
		return false;
}

const vector<userInfo> TIRoom::getUserInfo() const
{
	vector<UserInfo> userinfoAry;
	userinfoAry.reserve(m_userSet.size());
	const auto userCon = TObjectContainerFactory::get()->getUserContainer();

	for (const auto unique : m_userSet)
	{
		if(userCon->exist(unique))
		{
			UserInfo info(unique, userCon->at(unique)->getUserName());
			userinfoAry.emplace_back(info);
		}
	}

	return userinfoAry;
}

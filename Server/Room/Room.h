/*
 * TRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <list>
#include <map>
#include <string>
#include <memory>

#include "../../Commons/TType.h"
#include "../../Commons/TAtomic.h"

using namespace std;

class TServerUser;
class TRoom
{
public:
	virtual ~TRoom();

	typedef struct roomInfo
	{
		tetris::t_roomUnique unique;
		time_t makeTime;
		string roomName;
		map<tetris::t_roomUnique, shared_ptr<TServerUser>> users;
	};

	enum class property : std::uint16_t
	{
		LengthMin = 5,
		LengthMax = 20
	};

	inline const shared_ptr<roomInfo> getRoomInfo() const noexcept {return m_roominfo;	}

protected:
	TRoom() {}
	explicit TRoom(const std::string roomname, const std::list<shared_ptr<TServerUser>> userQ);
	

private:
	tetris::t_roomUnique m_unique;
	shared_ptr<roomInfo> m_roominfo;
	const bool addUser(shared_ptr<TServerUser> user);
	
};


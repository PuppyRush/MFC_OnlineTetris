/*
 * TRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <unordered_set>

#include "../../Commons/structs.h"
#include "../../Commons/TType.h"
#include "../../Commons/TAtomic.h"

class TServerUser;
class TRoom
{
public:
	virtual ~TRoom();

	enum class errorCode : tetris::t_error
	{
		Exist,
		Empty,
		Ok
	};

	enum class property : tetris::t_error
	{
		LengthMin = 5,
		LengthMax = 20
	};

	const errorCode add(const std::shared_ptr<TServerUser> room);
	const errorCode exit(const std::shared_ptr<TServerUser> room);
	const std::vector<UserInfo> getUserInfo() const;

	inline const std::shared_ptr<roomInfo> getRoomInfo() const noexcept {return m_roominfo;	}

protected:
	TRoom() {}
	explicit TRoom(const std::string roomname, const std::vector<std::shared_ptr<TServerUser>> userQ);

private:
	tetris::t_roomUnique m_unique;
	std::shared_ptr<roomInfo> m_roominfo;
	std::unordered_set<std::shared_ptr<TServerUser>> m_userSet;

	inline static TAtomic<tetris::t_roomUnique>& getAtomic()
	{
		static TAtomic<tetris::t_roomUnique> m_roomUniqueAtomic;
		return m_roomUniqueAtomic;
	}
};

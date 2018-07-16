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

#include "../structs.h"
#include "../TType.h"
#include "../TAtomic.h"
#include "../TObject.h"
#include "../TUser.h"
#include "../TSwitchingMessage.h"

class TIRoom : public TObject, public TMessenger
{
public:
	virtual ~TIRoom();

	enum class errorCode : tetris::t_error;

	virtual const TIRoom::errorCode add(const std::shared_ptr<TetrisUser> room) = 0;
	virtual const TIRoom::errorCode exit(const std::shared_ptr<TetrisUser> room) = 0;
	virtual const tetris::t_error switchingMessage(const tetris::msgElement &msg) = 0;

	const std::vector<UserInfo> getUserInfo() const;
	inline const std::shared_ptr<roomInfo> getRoomInfo() const noexcept {return m_roominfo;	}
	inline const tetris::t_roomUnique getUnique() const noexcept { return m_unique; }
protected:
	enum class errorCode : tetris::t_error
	{
		Exist,
		Empty,
		Ok
	};

	enum class property : tetris::t_property
	{
		LengthMin = 5,
			LengthMax = 20
	};

	TIRoom() {}
	explicit TIRoom(const std::string roomname);

	
	virtual const tetris::t_error _validator(const TIRoom &room) const = 0;

	inline static tetris::t_roomUnique getAtomic()
	{
		static TAtomic<tetris::t_roomUnique> m_roomUniqueAtomic;
		return m_roomUniqueAtomic.newUnique();
	}

	std::unordered_set<std::shared_ptr<TetrisUser>> m_userSet;

private:
	std::shared_ptr<roomInfo> m_roominfo;
	tetris::t_roomUnique m_unique;
};

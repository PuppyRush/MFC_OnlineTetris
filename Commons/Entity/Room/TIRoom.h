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

#include "../../structs.h"
#include "../../TAtomic.h"
#include "../TObject.h"
#include "../TUser.h"
#include "../../TObjectContainer.h"

class TIRoom : public TObject
{
public:

	enum class errorCode : tetris::t_error
	{
		Exist,
		Empty,
		Ok
	};

	enum class property : tetris::t_property
	{
		LengthMin = 5,
		LengthMax = 20,
	};

	enum class property_level : tetris::t_property
	{
		Begin = 0,
		Level1 = 0,
		Level2 = 1,
		Level3 = 2,
		Level4 = 3,
		Level5 = 4,
		Level6 = 5,
		Level7 = 6,
		Level8 = 7,
		Level9 = 8,
		End = Level9
	};

	enum class property_map : tetris::t_property
	{
		Begin = 0,
		stairway = 0,
		pyramid = 1,
		rainfall = 2,
		straight = 3,
		arbitrary = 4,
		empty = 5,
		random = 6,
		End = random
	};

	virtual ~TIRoom();

	const tetris::t_error enter(const UserInfo& userinfo);
	const tetris::t_error enter(const TetrisUser& userinfo);
	virtual const tetris::t_error exit(const tetris::t_unique user);
	virtual const bool exist(const tetris::t_unique unique) const;

	inline const size_t size() const { return m_userInfo.size(); }
	inline const size_t getRoomNumber() const { return m_roomInfo->roomNumber;	}
	const std::shared_ptr<std::vector<UserInfo>> getUserInfo() const;
	inline const std::shared_ptr<RoomInfo> getRoomInfo() const noexcept {return m_roomInfo;	}



protected:
	TIRoom();
	explicit TIRoom(const RoomInfo& roominfo);

	virtual const tetris::t_error _validator(const TIRoom &room) const = 0;

private:
	std::unordered_map<tetris::t_unique, std::shared_ptr<UserInfo>> m_userInfo;
	std::shared_ptr<RoomInfo> m_roomInfo;
	std::shared_ptr<TObjectContainer<TetrisUser>> m_userCon;
};

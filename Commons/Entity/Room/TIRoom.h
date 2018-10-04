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
		Begin = 1ull << 0,
		Level1 = 1ull << 1,
		Level2 = 1ull << 2,
		Level3 = 1ull << 3,
		Level4 = 1ull << 4,
		Level5 = 1ull << 5,
		Level6 = 1ull << 6,
		Level7 = 1ull << 7,
		Level8 = 1ull << 8,
		Level9 = 1ull << 9,
		End = 1ull << 10
	};

	enum class property_map : tetris::t_property
	{
		Begin = 1ull << 0 ,
		stairway = 1ull << 0,
		pyramid = 1ull << 1,
		rainfall = 1ull << 2,
		straight = 1ull << 3,
		arbitrary = 1ull << 4,
		empty = 1ull << 5,
		random = 1ull << 6,
		End = 1ull << 7
	};

	virtual ~TIRoom();
	virtual const bool exist(const tetris::t_unique unique) const;

	const tetris::t_error enter(const UserInfo &userinfo);
	virtual const tetris::t_error exit(const tetris::t_unique user, const property_distinguish otherDist);

	void setRoomNumber(const size_t num) { this->m_roomInfo->roomNumber = num; }
	const std::shared_ptr<std::vector<UserInfo>> getUserInfo() const;
	inline const size_t getRoomNumber() const { return m_roomInfo->roomNumber;	}
	inline const size_t size() const { return m_userInfo.size(); }
	inline const std::shared_ptr<RoomInfo> getRoomInfo() const noexcept {return m_roomInfo;	}

protected:
	property_distinguish m_dist;
    std::shared_ptr<TObjectContainer<TetrisUser>> m_userCon;

	TIRoom(property_distinguish dist);
	explicit TIRoom(const RoomInfo& roominfo, property_distinguish dist);
	virtual const tetris::t_error _validator(const TIRoom &room) const = 0;

private:
	std::unordered_map<tetris::t_unique, std::shared_ptr<UserInfo>> m_userInfo;
	std::shared_ptr<RoomInfo> m_roomInfo;


};

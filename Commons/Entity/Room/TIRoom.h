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
#include "../../TType.h"
#include "../../TAtomic.h"
#include "../TObject.h"
#include "../TUser.h"
#include "../../TObjectContainer.h"

class TIRoom : public TObject
{
public:
	virtual ~TIRoom();

	enum class errorCode : tetris::t_error;

	virtual const tetris::t_error add(const tetris::t_ptr<UserInfo> userinfo);
	virtual const tetris::t_error exit(const tetris::t_unique user);
	virtual const bool exist(const tetris::t_unique unique) const;

	inline const size_t size() const { return m_userInfo.size(); }
	inline const size_t roomNumber() const { return m_roomInfo->roomNumber;	}
	const std::shared_ptr<std::vector<UserInfo>> getUserInfo() const;
	inline const std::shared_ptr<roomInfo> getRoomInfo() const noexcept {return m_roomInfo;	}


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
		LengthMax = 20,
	};

	TIRoom() {}
	explicit TIRoom(const std::shared_ptr<RoomInfo> roominfo, const std::vector<UserInfo>& userinfoAry);

	virtual const tetris::t_error _validator(const TIRoom &room) const = 0;

private:
	std::shared_ptr<TObjectContainer<TetrisUser>> m_userCon;
	std::unordered_map<tetris::t_unique, std::shared_ptr<userInfo>> m_userInfo;
	std::shared_ptr<roomInfo> m_roomInfo;
};

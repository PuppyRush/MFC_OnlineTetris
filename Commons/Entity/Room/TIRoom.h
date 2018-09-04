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
#include "../../TMessenger.h"
#include "../TObject.h"
#include "../TUser.h"

class TIRoom : public TObject, public TMessenger
{
public:
	virtual ~TIRoom();

	enum class errorCode : tetris::t_error;

	virtual const tetris::t_error add(const tetris::t_unique user);
	virtual const tetris::t_error exit(const tetris::t_unique user);
	virtual const bool exist(const tetris::t_unique unique) const;

	inline const size_t size() const;
	const std::vector<UserInfo> getUserInfo() const;
	inline const std::shared_ptr<roomInfo> getRoomInfo() const noexcept {return m_roominfo;	}

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

	explicit TIRoom(const std::string roomname);

	virtual const tetris::t_error _validator(const TIRoom &room) const = 0;

	std::string m_roomname;

private:
	std::unordered_set<tetris::t_unique> m_userSet;
	std::shared_ptr<roomInfo> m_roominfo;
};

/*
 * TGameRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_map>
#include <mutex>

#include "../../Commons/Room/TIGameRoom.h"
#include "../../Commons/TType.h"
#include "../../Commons/TAtomic.h"

class TGameRoom : public TIGameRoom
{
public:

	enum class errorCode : tetris::t_error
	{
		Ok,
		DuplicatedRoomName = 0,
		OverNameLength,
		PassedTime,
		Nobody
	};

	enum class property : tetris::t_property
	{
		Size = 8
	};

	explicit TGameRoom(const tetris::t_roomUnique roomUnique, const std::string roomname);
	virtual ~TGameRoom();

    virtual void registryMessage() override;

	inline static std::shared_ptr<TGameRoom> makeShared(const std::string roomname)
	{
		static auto waitingRoom = std::make_shared<TGameRoom>(TIRoom::getAtomic(), roomname);
		return waitingRoom;
	}

private:
	std::unordered_map< tetris::t_roomUnique, std::shared_ptr<TIGameRoom>> m_roomMap;
	const tetris::t_error _validator(const TIRoom &room) const override;
};

/*
 * TGameRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_map>
#include <mutex>

#include "../../Commons/Entity/Room/TIGameRoom.h"
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

	explicit TGameRoom(const RoomInfo& roomname);
	virtual ~TGameRoom();

    virtual void registryMessage() override;

	inline static std::shared_ptr<TGameRoom> makeShared(const RoomInfo& room)
	{
		static auto waitingRoom = std::make_shared<TGameRoom>(room);
		return waitingRoom;
	}

	static bool makeGameRoom(const RoomInfo& room);

private:
	std::unordered_map< tetris::t_unique, std::shared_ptr<TIGameRoom>> m_roomMap;
	const tetris::t_error _validator(const TIRoom &room) const override;
};

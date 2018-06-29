/*
 * TWaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_map>
#include <mutex>

#include "Room.h"

#include "../../Commons/TType.h"
#include "../../Commons/TAtomic.h"
#include "../Server/TServerUser.h"


class TWaitingRoom : public TRoom
{
public:
	
	enum class errorCode : std::uint16_t
	{
		Ok,
		Duplicated=0,
		NameLength,
		PassedTime,
		Nobody
	};

	TWaitingRoom() {}
	explicit TWaitingRoom(const string roomname, const list<shared_ptr<TServerUser>> userQ);
	virtual ~TWaitingRoom();

	inline static shared_ptr<TWaitingRoom> getWaitingRoom() noexcept
	{
		auto waitingRoom = make_shared<TWaitingRoom>();
		return waitingRoom;
	}

	const errorCode insertRoom(const TRoom &room);

protected:
	std::unordered_map< tetris::t_roomUnique, shared_ptr<TWaitingRoom>> m_roomMap;

private:
	TAtomic<tetris::t_roomUnique> m_unique;

	const errorCode validator(const TRoom &room) const;
};

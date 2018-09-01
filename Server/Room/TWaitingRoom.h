/*
 * TWaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_set>
#include <memory>

#include "../../Commons/Entity/Room/TIWaitingRoom.h"
#include "../../Commons/Entity/TUser.h"
#include "../../Commons/TMessenger.h"


class TWaitingRoom : public TIWaitingRoom
{
public:
	virtual ~TWaitingRoom();

	enum class property : tetris::t_error
	{
		Size = 200
	};

	virtual void registryMessage() override;

	inline static std::shared_ptr<TWaitingRoom> getWaitingRoom()
	{
		const auto unique = TIRoom::getAtomic();
		static auto waitingRoom = std::shared_ptr<TWaitingRoom>(new TWaitingRoom(unique));
		return waitingRoom;
	}

	virtual const tetris::t_error _validator(const TIRoom &room) const override;



protected:

private:
	TWaitingRoom(const tetris::t_roomUnique roomUnique);
};

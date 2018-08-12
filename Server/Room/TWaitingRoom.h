/*
 * TWaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_set>
#include <memory>

#include "../../Commons/Room/TIWaitingRoom.h"
#include "../../Commons/TSwitchingMessage.h"
#include "../../Commons/TUser.h"

class TWaitingRoom : public TIWaitingRoom
{
public:
	virtual ~TWaitingRoom();

	enum class property : tetris::t_error
	{
		Size = 200
	};

	virtual const TIRoom::errorCode add(const std::shared_ptr<TetrisUser> room) override;
	virtual const TIRoom::errorCode exit(const std::shared_ptr<TetrisUser> room) override;
	virtual const tetris::t_error switchingMessage(const tetris::msgElement &msg) override;

	inline static std::shared_ptr<TWaitingRoom> getWaitingRoom()
	{
		static auto waitingRoom = std::shared_ptr<TWaitingRoom>(new TWaitingRoom());
		return waitingRoom;
	}

	virtual const tetris::t_error _validator(const TIRoom &room) const override;

protected:

private:
	TWaitingRoom() {}
};

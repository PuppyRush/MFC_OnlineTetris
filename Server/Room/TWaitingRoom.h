/*
 * TWaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include "TRoom.h"
#include "../../Commons/TSwitchingMessage.h"
#include "../Server/TServerUser.h"

class TWaitingRoom : public TRoom, public TSwitchingMessage
{
public:
	virtual const tetris::t_error TWaitingRoom::switchingMessage(const tetris::msgElement &msg) override;
	virtual ~TWaitingRoom();

	enum class property : tetris::t_error
	{
		Size = 200
	};

	inline static shared_ptr<TWaitingRoom> getWaitingRoom()
	{
		static auto waitingRoom = shared_ptr<TWaitingRoom>(new TWaitingRoom());
		return waitingRoom;
	}
private:
	TWaitingRoom() {}
	
};

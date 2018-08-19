/*
 * TWaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_set>
#include <memory>

#include "../../Commons/Room/TIRoom.h"
#include "../../Commons/TSwitchingMessage.h"
#include "../../Commons/TUser.h"

class TIWaitingRoom : public TIRoom
{
public:

	inline bool operator!=(const TIWaitingRoom& room)
	{
		return	getUnique() != room.getUnique();
	}

protected:
	virtual ~TIWaitingRoom() {}
	TIWaitingRoom() {}

	
};

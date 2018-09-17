/*
 * TWaitingRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_set>
#include <memory>

#include "../../structs.h"
#include "TIRoom.h"
#include "../TUser.h"


class TIWaitingRoom : public TIRoom
{
public:
	virtual ~TIWaitingRoom() {}

	static const std::shared_ptr<std::vector<RoomInfo>> getWaitingRoomsInfo();

protected:
	TIWaitingRoom() {}
	explicit TIWaitingRoom(const std::shared_ptr<RoomInfo> roominfo, const std::vector<UserInfo>& userinfoAry);

};

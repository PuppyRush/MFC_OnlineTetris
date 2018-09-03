/*
 * TGameRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_map>
#include <mutex>

#include "TIRoom.h"
#include "../TType.h"
#include "../TAtomic.h"
#include "../TMessenger.h"

class TIGameRoom : public TIRoom
{
public:
	virtual ~TIGameRoom() {}

protected:
	TIGameRoom(const std::string roomname);


	std::unordered_map< tetris::t_unique, std::shared_ptr<TIGameRoom>> m_roomMap;
};

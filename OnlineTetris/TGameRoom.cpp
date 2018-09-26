#include "stdafx.h"
#include "TGameRoom.h"


TGameRoom::TGameRoom()
{
}


TGameRoom::~TGameRoom()
{
}

void TGameRoom::registryMessage()
{
	this->addCaller(make_pair(toUType(GAMEROOM_MSG::CREATE_GAMEROOM), std::bind(&TGameRoom::createGameroom, this, std::placeholders::_1)));
}

const tetris::t_error TGameRoom::_validator(const TIRoom &room) const
{


	return toUType(TIRoom::errorCode::Ok);
}

void TGameRoom::createGameroom(const TMessageObject& msg)
{
}
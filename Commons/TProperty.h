#pragma once

#include "TType.h"

enum class property_error : tetris::t_property
{
	eFail=0,
	eOK = 1
};

enum class property_distinguish : tetris::t_dist
{
	User =  1ull << 0,
	Socket =  1ull << 1,
	WaitingRoom =  1ull << 2,
	GameRoom =  1ull << 3,
};

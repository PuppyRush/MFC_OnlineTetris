#pragma once

#include "TType.h"

enum class property_error : tetris::t_property
{
	eFail=0,
	eOK = 1
};

enum class property_distinguish : tetris::t_dist
{
	Begin = 1ull << 0,
	User =  1ull << 1,
	Socket =  1ull << 2,
	WaitingRoom =  1ull << 3,
	GameRoom =  1ull << 4,
	End = 1ull << 5
};

#pragma once

#include "TType.h"

class TSwitchingMessage
{
	virtual const tetris::t_error switchingMessage(const tetris::msgElement &msg) = 0;
};


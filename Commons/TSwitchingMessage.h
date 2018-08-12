#pragma once

#include "TType.h"

class TMessenger
{
public:
	virtual const tetris::t_error switchingMessage(const tetris::msgElement &msg) = 0;
	TMessenger() {}
	virtual ~TMessenger() {}
protected:
	

private:
};

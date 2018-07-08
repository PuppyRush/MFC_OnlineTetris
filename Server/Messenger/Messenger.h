#pragma once

#include <unordered_set>

#include "../../Commons/TSwitchingMessage.h"

class MessengerImpl : public Messenger
{
public:

protected:
	MessengerImpl() {}
	virtual ~MessengerImpl() {}

	virtual const tetris::t_error switchingMessage(const tetris::msgElement &msg) = 0;

private:
};


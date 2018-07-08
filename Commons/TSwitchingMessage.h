#pragma once

#include "TType.h"
#include "TObjectContainer.h"
#include "TUser.h"
#include "Uncopyable.h"

class Messenger : public Uncopyable
{
protected:
	explicit Messenger(TObjectContainer<tetris::t_userUnique, TetrisUser> TUserContainer);
	virtual ~Messenger() {}

	virtual const tetris::t_error switchingMessage(const tetris::msgElement &msg) = 0;

private:
	TObjectContainer<tetris::t_userUnique, TetrisUser> m_TUserContainer;
};

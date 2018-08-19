#pragma once

#include "TType.h"
#include "unordered_map"


class TMessenger
{
public:
	tetris::t_error sendMessage(const tetris::msgElement &msg);
	bool isRegsiteMessage(const tetris::t_msgidx msgidx);

	virtual const tetris::t_error regsiteMessage() = 0;

	TMessenger() {}
	virtual ~TMessenger() {}

protected:
	std::unordered_map<tetris::t_msgidx, std::function<void(const tetris::msgElement&)>> m_messageCaller;

private:
	const tetris::t_error switchingMessage(const tetris::t_msgidx , const tetris::msgElement &msg);
	void addCaller(const std::pair<tetris::t_msgidx, std::function<void(const tetris::msgElement&)>> key_value);

};

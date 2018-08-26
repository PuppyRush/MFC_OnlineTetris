#pragma once

#include <functional>
#include "TType.h"
#include "unordered_map"


class TMessenger
{
public:
	void sendMessage(const tetris::msgElement &msg);

	TMessenger();
	virtual ~TMessenger() {}

protected:
	std::unordered_map<tetris::t_msgidx, std::function<void(const tetris::msgElement&)>> m_messageCaller;

	virtual void registryMessage() = 0;

	bool isRegsiteMessage(const tetris::t_msgidx msgidx);
	void addCaller(const std::pair<tetris::t_msgidx, std::function<void(const tetris::msgElement&)>> key_value);

private:
	const void switchingMessage(const tetris::t_msgidx , const tetris::msgElement &msg);


};

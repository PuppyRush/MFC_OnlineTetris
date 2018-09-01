#pragma once

#include <functional>
#include <unordered_map>
#include <queue>

#include "TypeTraits.h"
#include "TType.h"
#include "TFunctional.h"

class TMessenger
{
public:
	TMessenger();
	virtual ~TMessenger();

	void push(const tetris::msgElement &msg);
	const tetris::msgElement pop();
	void send(const tetris::msgElement &msg);

protected:
	std::unordered_map<tetris::t_msgidx, std::function<void(const tetris::msgElement&)>> m_messageCaller;
	std::priority_queue<tetris::msgElement, std::vector<tetris::msgElement>, messageComp> m_recvQ;
	std::priority_queue<tetris::msgElement, std::vector<tetris::msgElement>, messageComp> m_sendQ;

	virtual void registryMessage() = 0;
	bool isRegsiteMessage(const tetris::t_msgidx msgidx);
	void addCaller(const std::pair<tetris::t_msgidx, std::function<void(const tetris::msgElement&)>> key_value);

private:
	const void _switchingMessage(const tetris::t_msgidx , const tetris::msgElement &msg);

};

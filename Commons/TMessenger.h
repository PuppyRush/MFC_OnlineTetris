#pragma once

#include <functional>
#include <unordered_map>
#include <queue>
#include <mutex>

#include "TMessageObject.h"

class TMessenger
{
public:
	TMessenger();
	virtual ~TMessenger();

	void send(const TMessageObject msg);

protected:
	std::unordered_map<tetris::t_msgidx, std::function<void(const TMessageObject&)>> m_messageCaller;


	virtual void registryMessage() = 0;
	bool isRegsiteMessage(const tetris::t_msgidx msgidx);
	void addCaller(const std::pair<tetris::t_msgidx, std::function<void(const TMessageObject&)>> key_value);

private:
	const void _switchingMessage(const tetris::t_msgidx , const TMessageObject& msg);

};
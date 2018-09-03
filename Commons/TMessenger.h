#pragma once

#include <functional>
#include <unordered_map>
#include <queue>
#include <mutex>

#include "TypeTraits.h"
#include "TType.h"
#include "TFunctional.h"


class TMessenger
{
public:
	TMessenger();
	virtual ~TMessenger();

	/*inline static void push(const tetris::msgElement &msg)
	{
		std::lock_guard<std::mutex> lock(m_qMutex);
		m_sendQ.push(msg);
	}

	inline static const tetris::msgElement pop()
	{
		std::lock_guard<std::mutex> lock(m_qMutex);
		const auto msg = m_sendQ.top();
		m_sendQ.pop();
		return msg;
	}

	inline static const bool exist()
	{
		std::lock_guard<std::mutex> lock(m_qMutex);
		return m_sendQ.empty();
	}*/

	void send(const tetris::msgElement &msg);

protected:
	std::unordered_map<tetris::t_msgidx, std::function<void(const tetris::msgElement&)>> m_messageCaller;


	virtual void registryMessage() = 0;
	bool isRegsiteMessage(const tetris::t_msgidx msgidx);
	void addCaller(const std::pair<tetris::t_msgidx, std::function<void(const tetris::msgElement&)>> key_value);

private:
	/*static std::priority_queue<tetris::msgElement, std::vector<tetris::msgElement>, messageComp> m_sendQ;
	static std::mutex	m_qMutex;*/

	const void _switchingMessage(const tetris::t_msgidx , const tetris::msgElement &msg);


};
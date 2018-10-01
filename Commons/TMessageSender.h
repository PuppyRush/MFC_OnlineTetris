#pragma once

#include <queue>
#include <mutex>
#include <algorithm>
#include <memory>

#include "Uncopyable.h"
#include "TType.h"
#include "TMessageObject.h"

#define T_SEND(socket, msg) TMessageSender::get()->push(TMessageObject::toMessage(socket, msg))

class TMessageSender : public Uncopyable
{
public:
	virtual ~TMessageSender();

	void run();
	const TMessageObject pop();

	inline void push(const TMessageObject& msg)
	{
		std::lock_guard<std::mutex> lock(m_qMutex);
		m_sendQ.push(msg);
	}

	inline const bool exist()
	{
		std::lock_guard<std::mutex> lock(m_qMutex);
		return m_sendQ.empty();
	}

	static std::shared_ptr<TMessageSender> get()
	{
		static std::shared_ptr<TMessageSender> sender = std::shared_ptr<TMessageSender>(new TMessageSender);
		return sender;
	}

private:
	TMessageSender()
	:m_isContinue(true)
	{}

	std::queue<TMessageObject> m_messqgeQ;
	std::priority_queue<TMessageObject, std::vector<TMessageObject>, std::greater<TMessageObject>> m_sendQ;
	std::mutex	m_qMutex;
	bool m_isContinue;
};


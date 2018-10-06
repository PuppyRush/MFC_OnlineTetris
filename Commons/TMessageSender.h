#pragma once

#include <queue>
#include <mutex>
#include <algorithm>
#include <memory>
#include <condition_variable>

#include "Uncopyable.h"
#include "TType.h"
#include "TMessageObject.h"

#define T_SEND(socket, msg) TMessageSender::get()->push(TMessageObject::toMessage(socket, msg))
#define T_BROADCAST(msg) TMessageSender::get()->push(TMessageObject::toMessage(msg))

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
		m_cond.notify_one();
	}

	inline const bool exist()
	{
		std::unique_lock<std::mutex> lock(m_qMutex);
		m_cond.wait(lock, [=](){return !m_sendQ.empty() || !m_isContinue;});

		return m_sendQ.empty();
	}

	static std::shared_ptr<TMessageSender> get()
	{
		static std::shared_ptr<TMessageSender> sender = std::shared_ptr<TMessageSender>(new TMessageSender);
		return sender;
	}

private:
	std::priority_queue<TMessageObject, std::vector<TMessageObject>, std::greater<TMessageObject>> m_sendQ;
	std::mutex	m_qMutex;
	bool m_isContinue;
	std::condition_variable m_cond;

	TMessageSender()
	:m_isContinue(true)
	{}


};


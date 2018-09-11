#pragma once

#include <queue>
#include <mutex>
#include <algorithm>
#include <memory>

#include "Uncopyable.h"
#include "TType.h"
#include "TMessageObject.h"

class TMessageSender : public Uncopyable
{
public:
	virtual ~TMessageSender();

	inline void push(const TMessageObject& msg)
	{
		std::lock_guard<std::mutex> lock(m_qMutex);
		m_sendQ.push(msg);
	}

	inline const TMessageObject pop()
	{
		
		while (m_isContinue)
		{
			if (m_sendQ.empty())
				continue;

			std::lock_guard<std::mutex> lock(m_qMutex);

			const auto msg = m_sendQ.top();
			m_sendQ.pop();
			return msg;
		}
		
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

	std::priority_queue<TMessageObject, std::vector<TMessageObject>, std::greater<TMessageObject>> m_sendQ;
	std::mutex	m_qMutex;
	bool m_isContinue;
};


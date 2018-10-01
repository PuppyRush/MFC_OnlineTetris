#include "TMessageSender.h"


TMessageSender::~TMessageSender()
{
	m_isContinue = false;
}

void TMessageSender::run()
{

}

const TMessageObject TMessageSender::pop()
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
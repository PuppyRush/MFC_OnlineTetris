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
	std::unique_lock<std::mutex> lock(m_qMutex);
	m_cond.wait(lock, [=](){return !m_sendQ.empty() || !m_isContinue;});

	if(m_sendQ.empty() || !m_isContinue)
		return TMessageObject::emptyMessage();

	const auto msg = m_sendQ.top();
	m_sendQ.pop();
	return msg;
}
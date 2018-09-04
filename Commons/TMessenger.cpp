#include "TMessenger.h"

#include "TypeTraits.h"
#include "TMessageStruct.h"

TMessenger::TMessenger()
{
}

TMessenger::~TMessenger()
{
	/*while (!m_sendQ.empty())
	{
		auto msg = m_sendQ.top();
		m_sendQ.pop();
		delete[] msgHelper::getMessage(msg);
	}*/

}

void TMessenger::addCaller(const std::pair<tetris::t_msgidx, std::function<void(const TMessageObject&)>> registee)
{
	if(registee.second==nullptr)
		return;

	m_messageCaller.insert(registee);
}

bool TMessenger::isRegsiteMessage(const tetris::t_msgidx msgidx)
{
	if(m_messageCaller.count(msgidx))
		return true;
	else
		return false;
}

void TMessenger::send(const TMessageObject msg)
{
	const auto msgidx = Header::getMsgidx(msg.getMessage());
	if (isRegsiteMessage(msgidx))
		_switchingMessage(msgidx, msg);
}

const void TMessenger::_switchingMessage(const tetris::t_msgidx msgidx, const TMessageObject& msg)
{
	m_messageCaller.at(msgidx)(msg);
}


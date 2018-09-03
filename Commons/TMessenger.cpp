#include "TMessenger.h"

#include "TypeTraits.h"
#include "TMessage.h"

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

void TMessenger::addCaller(const std::pair<tetris::t_msgidx, std::function<void(const tetris::msgElement&)>> registee)
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

void TMessenger::send(const tetris::msgElement &msg)
{
	const tetris::t_msgidx msgidx = Header::getMsgidx(msgHelper::getMessage(msg));
	if (isRegsiteMessage(msgidx))
		_switchingMessage(msgidx, msg);
}

const void TMessenger::_switchingMessage(const tetris::t_msgidx msgidx, const tetris::msgElement &msg)
{
	m_messageCaller.at(msgidx)(msg);
}


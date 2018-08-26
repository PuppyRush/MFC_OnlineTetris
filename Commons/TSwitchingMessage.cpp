#include "TSwitchingMessage.h"

#include "TypeTraits.h"
#include "MessageHeader.h"

TMessenger::TMessenger()
{
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

void TMessenger::sendMessage(const tetris::msgElement &msg)
{
	const tetris::t_msgidx msgidx = Header::getMsgidx(msgHelper::getMessage(msg));
	if (isRegsiteMessage(msgidx))
		switchingMessage(msgidx, msg);
}

const void TMessenger::switchingMessage(const tetris::t_msgidx msgidx, const tetris::msgElement &msg)
{
	m_messageCaller.at(msgidx)(msg);
}
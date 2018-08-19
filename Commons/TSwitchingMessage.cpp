#include "TSwitchingMessage.h"

#include "TypeTraits.h"
#include "MessageHeader.h"

void TMessenger::addCaller(const std::pair<tetris::t_msgidx, std::function<void(const tetris::msgElement&)>> registee)
{

	if(registee.second==nullptr)
		return;

	m_messageCaller.insert(registee);
}

bool TMessenger::isRegsiteMessage(const tetris::t_msgidx msgidx)
{
	if(m_messageCaller.count(msgidx)>0)
		return true;
	else
		return false;
}

tetris::t_error TMessenger::sendMessage(const tetris::msgElement &msg)
{
	const tetris::t_msgidx msgidx = Header::getMsgidx(msgHelper::getMessage(msg));
	if(isRegsiteMessage(msgidx))
		return switchingMessage(msgidx, msg);
	else
		return false;
}

const tetris::t_error TMessenger::switchingMessage(const tetris::t_msgidx msgidx, const tetris::msgElement &msg)
{
	m_messageCaller.at(msgidx)(msg);
}
#include "Entity/TObject.h"



void TObject::addCaller(const std::pair<tetris::t_msgidx, std::function<void(const TMessageObject&)>> registee)
{
	if (registee.second == nullptr)
		return;

	m_messageCaller.insert(registee);
}

bool TObject::isRegsiteMessage(const tetris::t_msgidx msgidx)
{
	if (m_messageCaller.count(msgidx))
		return true;
	else
		return false;
}

void TObject::send(const TMessageObject& msg)
{
	const auto msgidx = Header::getMsgidx(msg.getMessage());
	if (isRegsiteMessage(msgidx))
		_switchingMessage(msgidx, msg);
}

const void TObject::_switchingMessage(const tetris::t_msgidx msgidx, const TMessageObject& msg)
{
	m_messageCaller.at(msgidx)(msg);
}


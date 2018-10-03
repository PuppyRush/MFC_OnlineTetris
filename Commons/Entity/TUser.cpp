#pragma once

#include <memory.h>

#include "../TMessageSender.h"
#include "TUser.h"
#include "TSocket.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TetrisUser::TetrisUser(const tetris::t_socket socket)
	:m_chat(std::make_shared<TChat>()),
	m_socketUnique(socket)
{}

void TetrisUser::removeFilter(const tetris::t_unique unique)
{
	m_chat->removeFilter(unique);
}

void TetrisUser::addFilter(const tetris::t_unique unique)
{
	m_chat->addFilter(unique);
}

void TetrisUser::sendChatMessage(const std::string str)
{
	m_chat->add(this->getUnique(), str);

	Client client(this->getUnique(), true);
	mChatMessage chatMessage(Header(toUType(Priority::Normal), toUType(CLIENT_MSG::SEND_MESSAGE)),
		client, str.size(), str.c_str(), std::numeric_limits<tetris::t_unique>::max(), toUType(TChat::property_chat::SendMsg));

	T_SEND(m_socketUnique, &chatMessage);
}

void TetrisUser::sendWhisperMessage(const tetris::t_unique receiver, const std::string str)
{
	m_chat->addWhisper(this->getUnique(), receiver, str);

	Client client(this->getUnique(), true);
	mChatMessage chatMessage(Header(toUType(Priority::Normal), toUType(CLIENT_MSG::SEND_MESSAGE)),
		client, str.size(), str.c_str(), receiver, toUType(TChat::property_chat::SendWhisper));

	T_SEND(m_socketUnique, &chatMessage);
}

void TetrisUser::clear()
{
	m_chat->clear();
}
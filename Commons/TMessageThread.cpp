#include "TMessageThread.h"
#include "TypeTraits.h"
#include "Entity/TSocket.h"
#include "TMessageSender.h"
#include "TObjectContainerFactory.h"

#include <queue>

using namespace std;

TMessageThread::TMessageThread()
	:m_continue(true),
	m_recvThread(nullptr),
	m_sendThread(nullptr)
{
	auto factory = TObjectContainerFactory::get();
	m_userCon = factory->getContainer<TetrisUser>(property_distinguish::User);
	m_socketCon = factory->getContainer<TetrisSocket>(property_distinguish::Socket);
	m_gameroomCon = factory->getContainer<TIGameRoom>(property_distinguish::GameRoom);
	m_waitingroomCon = factory->getContainer<TIWaitingRoom>(property_distinguish::WaitingRoom);
}

TMessageThread::~TMessageThread()
{
	end();
}

void TMessageThread::run()
{
	const auto recvfn = &TMessageThread::_recv;
	m_recvThread = make_shared<thread>(recvfn, this);

	const auto sendfn = &TMessageThread::_send;
	m_sendThread = make_shared<thread>(sendfn, this);

}

void TMessageThread::end()
{
	m_continue = false;
}

void TMessageThread::_send()
{
	auto sender = TMessageSender::get();
	while (m_continue)
	{
		if (sender->exist())
		{
			const auto msg = sender->pop();
			const auto sender = msg.getSocket();

			if (m_socketCon->exist(sender))
				m_socketCon->at(sender)->send(msg);
		}
	}
}

void TMessageThread::_recv()
{
	auto sender = TMessageSender::get();
	while (m_continue)
	{
		for (const auto socket : *m_socketCon)
		{
			auto msg = socket->recv();
			if (msg.getSize() > 0)
			{
				for (const auto obj : *m_userCon)
					obj->send(msg);

				for (const auto obj : *m_gameroomCon)
					obj->send(msg);

				for (const auto obj : *m_waitingroomCon)
					obj->send(msg); 
			}
		}
	}
}

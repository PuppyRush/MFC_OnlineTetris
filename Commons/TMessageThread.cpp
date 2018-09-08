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
	m_userCon = factory->getUserContainer().get();
	m_socketCon = factory->getSocketContainer().get();
	m_gameroomCon = factory->getGameRoomContainer().get();
	m_waitingroomCon = factory->getWaitingRoomContainer().get();
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

	//const auto popfn = &TMessageThread::_switchingMessage;
	//m_popThread = make_shared<thread>(popfn, this);
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
		//if(TMessenger::exist())
		//	continue;

		const auto msg = sender->pop();
		const auto sender = msg.getSocket();

		if (m_socketCon->exist(sender))
			m_socketCon->at(sender)->send(msg);
	}
}

void TMessageThread::_recv()
{
	auto container = TObjectContainerFactory::get()->getSocketContainer();
	auto sender = TMessageSender::get();
	while (m_continue)
	{
		//if (container->isRefreshing())
		//	continue;

		for (const auto socket : *container)
		{
			auto msg = socket->recv();
			if (msg.getSize() > 0)
			{
				for (const auto obj : *m_userCon)
					obj->send(msg);

				for (const auto obj : *m_socketCon)
					obj->send(msg);

				for (const auto obj : *m_gameroomCon)
					obj->send(msg);

				for (const auto obj : *m_waitingroomCon)
					obj->send(msg); 
			}
		}
	}
}

void TMessageThread::_switchingMessage()
{
	while (m_continue)
	{
       

        
	}
}

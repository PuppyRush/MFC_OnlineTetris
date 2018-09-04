#include "TMessageThread.h"
#include "TypeTraits.h"
#include "Entity/TSocket.h"
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

	const auto popfn = &TMessageThread::_switchingMessage;
	m_popThread = make_shared<thread>(popfn, this);
}

void TMessageThread::end()
{
	m_continue = false;
}

void TMessageThread::_send()
{
	while (m_continue)
	{

		//if(TMessenger::exist())
		//	continue;

		//const auto msg = TMessenger::pop();

		/*for(const auto user : *m_userCon)
			msgQ.push(user->pop())*/

		/*for (const auto socket : *container)
			socket->send();*/
	}
}

void TMessageThread::_recv()
{
	auto container = TObjectContainerFactory::get()->getSocketContainer();
	while (m_continue)
	{
		if (container->isRefreshing())
			continue;

		for (const auto socket : *container)
		{
			auto msg = socket->recv();
			/*if(msgHelper::getSize(msg)>0)
				m_messageQ.push(msg);*/
		}
	}
}

void TMessageThread::_switchingMessage()
{
	while (m_continue)
	{
       /* m_userCon->refresh();
		m_gameroomCon->refresh();
		m_waitingroomCon->refresh();
		m_socketCon->refresh();

		if (m_messageQ.empty())
			continue;

		const auto msg = m_messageQ.top();
		m_messageQ.pop();

        for (const auto obj : *userCon)
			obj->send(msg);

        for (const auto obj : *socketCon)
			obj->send(msg);

		for (const auto obj : *gameroomCon)
			obj->send(msg);

		for (const auto obj : *waitroomCon)
			obj->send(msg);*/
	}
}

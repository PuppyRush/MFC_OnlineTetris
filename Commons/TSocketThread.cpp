#include "TSocketThread.h"
#include "TypeTraits.h"
#include "TSocket.h"
#include "TObjectContainerFactory.h"

using namespace std;

TSocketThread::TSocketThread()
	:m_continue(true),
	m_recvThread(nullptr),
	m_sendThread(nullptr)
{
}

TSocketThread::~TSocketThread()
{
	end();
}

void TSocketThread::run()
{
	const auto recvfn = &TSocketThread::_recv;
	m_recvThread = make_shared<thread>(recvfn, this);

	const auto sendfn = &TSocketThread::_send;
	m_sendThread = make_shared<thread>(sendfn, this);

	const auto popfn = &TSocketThread::_switchingMessage;
	m_popThread = make_shared<thread>(popfn, this);
}

void TSocketThread::end()
{
	m_continue = false;
}

void TSocketThread::_send()
{
	auto container = TObjectContainerFactory::get()->getSocketContainer();
	while (m_continue)
	{
		if (container->isRefreshing())
			continue;

		for (const auto user : *container)
			user->send();
		container->refresh();
	}
}

void TSocketThread::_recv()
{
	auto container = TObjectContainerFactory::get()->getSocketContainer();
	auto ptrMap = container->getMap();
	while (m_continue)
	{
		//if (container->isRefreshing())
		//	continue;

		for (const auto user : *container)
		{
			auto msg = user->recv();
			if(msgHelper::getSize(msg)>0)
				m_messageQ.push(msg);
		}

		container->refresh();
	}
}

void TSocketThread::_switchingMessage()
{
	auto factory = TObjectContainerFactory::get();

	auto gameroomCon = factory->getGameRoomContainer();
	auto waitroomCon = factory->getWaitingRoomContainer();
	auto userCon = factory->getUserContainer();

	while (m_continue)
	{
		if (m_messageQ.empty())
			continue;

		userCon->refresh();
		gameroomCon->refresh();
		waitroomCon->refresh();

		const auto msg = m_messageQ.front();
		m_messageQ.pop();

		for (const auto obj : *gameroomCon)
			obj->sendMessage(msg);

		for (const auto obj : *waitroomCon)
			obj->sendMessage(msg);

		for (const auto obj : *userCon)
			obj->sendMessage(msg);
	}
}

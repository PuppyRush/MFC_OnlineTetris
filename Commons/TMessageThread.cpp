#include "TMessageThread.h"
#include "TypeTraits.h"
#include "TSocket.h"
#include "TObjectContainerFactory.h"

using namespace std;

TMessageThread::TMessageThread()
	:m_continue(true),
	m_recvThread(nullptr),
	m_sendThread(nullptr)
{
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
	auto container = TObjectContainerFactory::get()->getSocketContainer();
	while (m_continue)
	{
		if (container->isRefreshing())
			continue;

		for (const auto socket : *container)
			socket->send();
	}
}

void TMessageThread::_recv()
{
	auto container = TObjectContainerFactory::get()->getSocketContainer();
	auto ptrMap = container->getMap();
	while (m_continue)
	{
		if (container->isRefreshing())
			continue;

		for (const auto socket : *container)
		{
			auto msg = socket->recv();
			if(msgHelper::getSize(msg)>0)
				m_messageQ.push(msg);
		}
	}
}

void TMessageThread::_switchingMessage()
{
	auto factory = TObjectContainerFactory::get();

    auto socketCon = TObjectContainerFactory::get()->getSocketContainer();
	auto gameroomCon = factory->getGameRoomContainer();
	auto waitroomCon = factory->getWaitingRoomContainer();
	auto userCon = factory->getUserContainer();

	while (m_continue)
	{

        userCon->refresh();
        gameroomCon->refresh();
        waitroomCon->refresh();
        socketCon->refresh();

		if (m_messageQ.empty())
			continue;

		const auto msg = m_messageQ.front();
		m_messageQ.pop();

        for (const auto obj : *userCon)
            obj->sendMessage(msg);

        for (const auto obj : *socketCon)
            obj->sendMessage(msg);

		for (const auto obj : *gameroomCon)
			obj->sendMessage(msg);

		for (const auto obj : *waitroomCon)
			obj->sendMessage(msg);
	}
}

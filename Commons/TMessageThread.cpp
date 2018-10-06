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
	m_userCon = factory->getContainer<TetrisUser>();
	m_socketCon = factory->getContainer<TetrisSocket>();
	m_gameroomCon = factory->getContainer<TIGameRoom>();
	m_waitingroomCon = factory->getContainer<TIWaitingRoom>();

	m_objcontainerAry.push_back(m_userCon);
	m_objcontainerAry.push_back(m_gameroomCon);
	m_objcontainerAry.push_back(m_waitingroomCon);
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
		const auto msg = sender->pop();
		const auto sender = msg.getSocket();

		if(msg.isBroadcast())
		{
			for(const auto socket : *m_socketCon)
				socket->send(msg);
		}
		else
		{
			if (m_socketCon->exist(sender))
				m_socketCon->at(sender)->send(msg);
		}

#ifdef WINDOWS_TETRIS
		if (msg.isExceptionMe())
		{
			for (const auto con : m_objcontainerAry)
			{
				for (auto it = con->begin(); it != con->end(); it++)
				{
					it->second->send(msg);
				}
			}
		}
#endif
	}
}

void TMessageThread::_recv()
{
	auto sender = TMessageSender::get();
	vector<tetris::t_socket> closedSockets;
	closedSockets.reserve(10);

	while (m_continue)
	{
		for (const auto socket : *m_socketCon)
		{
			auto msg = socket->recv();
			if (msg.getSize() > 0)
			{
				for (const auto con : m_objcontainerAry)
				{
					for (auto it = con->begin(); it != con->end(); it++)
					{
						it->second->send(msg);
					}
				}
			}
			else
			{
				closedSockets.push_back(socket->getSocket());
				socket->close();
				break;
			}
		}

		for (const auto socket : closedSockets)
		{
			m_socketCon->remove(socket);
		}
		closedSockets.clear();
	}
}

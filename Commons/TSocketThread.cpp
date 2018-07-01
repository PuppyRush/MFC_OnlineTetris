#include "TSocketThread.h"

TSocketThread::TSocketThread()
	:m_closeSocket(true),
	m_recvThread(nullptr),
	m_sendThread(nullptr)
{
}

TSocketThread::TSocketThread(const tetris::t_socket socket)
	:TSocketThread()
{
}

TSocketThread::TSocketThread(const unordered_set<tetris::t_socket>& sockets)
	:TSocketThread()
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
}


void TSocketThread::end()
{
	m_closeSocket = false;
}

void TSocketThread::_send()
{
	while (m_closeSocket)
	{
		for(const auto socket : m_sockets)
		{
			auto msgpair = socket->
			if (!msgpair.first)
				continue;
			const auto msg = msgpair.second;
			const auto realMsg = msgHelper::getMessage(msg);
			const auto size = msgHelper::getSize(msg);

			const auto written = socket->_sendTo(realMsg, size);
			if (written <= 0)
			{
				//writeLog("error sendto");
			}

			delete[] realMsg;
		}
	}
}

void TSocketThread::_recv()
{
	while (m_closeSocket)
	{
		auto msg = _recvFrom();
		if (msgHelper::getSize(msg) <= 0)
		{
			//writeLog("error recvfrom");
			continue;
		}
		else
			m_recvQ->push(msg);
	}
}

void add(shared_ptr<TetrisSocket> socket)
{

}

void remove(shared_ptr<TetrisSocket> socket)
{

}


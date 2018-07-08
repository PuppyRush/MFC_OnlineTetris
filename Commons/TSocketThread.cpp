#include "TSocketThread.h"

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
}


void TSocketThread::end()
{
	m_continue = false;
}

void TSocketThread::_send()
{
	//while (m_continue)
	//{
	//	for(const auto socket : m_sockets)
	//		socket->send();
	//}
}

void TSocketThread::_recv()
{
	//while (m_continue)
	//{
	//	for (const auto socket : m_sockets)
	//	{
	//		lock_guard<mutex> lck(m_recvMutex);
	//		socket->recv();
	//	}
	//}
}

const tetris::msgElement TSocketThread::pop()
{

}
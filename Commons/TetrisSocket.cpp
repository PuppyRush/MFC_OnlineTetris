#include "TetrisSocket.h"

using namespace tetris_socket;
using namespace msg_header;

TetrisSocket::TetrisSocket(const int domain, const int type, const int protocol)
	:m_closeSocket(true), 
	m_recvThread(nullptr),
	m_sendThread(nullptr),
	m_domain(domain),
	m_type(type),
	m_protocol(protocol)
{
}

TetrisSocket::~TetrisSocket()
{
	while(!m_recvQ.empty())
	{
		auto msg = m_recvQ.front();
		m_recvQ.pop();
		delete[] msg.first;
	}

	while(!m_sendQ.empty())
	{
		auto msg = m_sendQ.front();
		m_recvQ.pop();
		delete[] msg.first;
	}
}

void TetrisSocket::SetIP(const IPString &ip)
{
	m_ip = ip;
}

void TetrisSocket::SetPort(const unsigned port)
{
	m_port = port;
}

unsigned TetrisSocket::accept()
{
	unsigned err = 0;
	if(err = _accept() > 0)
		return err;
	_runAcception();

	return 0u;
}

unsigned TetrisSocket::connect()
{
	auto err = 0u;
	if(err = _connect() > 0)
		return err;
	_run();
	
	return 0u;
}

unsigned TetrisSocket::close()
{
	_end();
	return _close(m_socket);
}

void TetrisSocket::_run()
{
	const auto recvfn = &TetrisSocket::_recv;
	m_recvThread = make_shared<std::thread>(recvfn, this);

	const auto sendfn = &TetrisSocket::_send;
	m_sendThread = make_shared<std::thread>(sendfn, this);
}

void TetrisSocket::_runAcception()
{
	const auto acceptFn = &TetrisSocket::_acceptSocket;
	m_acceptThread = make_shared<std::thread>(acceptFn, this);
}

void TetrisSocket::_end()
{
	m_closeSocket = false;
}

void TetrisSocket::_send()
{
	while(m_closeSocket)
	{
		if(!m_sendQ.empty())
		{
			const auto msg = m_sendQ.front();
			m_sendQ.pop();
			
			const auto written = _sendTo(msg.first, msg.second);
			if(written <= 0)
			{
				m_closeSocket = false;
				//writeLog("error sendto");
			}
			else
				delete[] msg.first;
		}
	}
}

void TetrisSocket::_recv()
{
	while(m_closeSocket)
	{
		const auto msg = _recvFrom();
		if(msg.second <= 0)
		{
			m_closeSocket = false;
			//writeLog("error recvfrom");
			break;
		}

		m_recvQ.push(msg);
	}
}


void TetrisSocket::_acceptSocket()
{
	while(m_closeSocket)
	{
		const int socket = _accept();
		if(socket == -1)
		{
			//writeLog("error recvfrom");
		}

		m_acceptedSocketQ.push(socket);
	}
}

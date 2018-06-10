#include "TSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace tetris;

TetrisSocket::TetrisSocket(const int domain, const int type, const int protocol, const IPString ip, const portType port)
	:m_closeSocket(true), 
	m_recvThread(nullptr),
	m_sendThread(nullptr),
	m_domain(domain),
	m_type(type),
	m_protocol(protocol),
	m_port(port),
	m_ip(ip),
	m_socket(0)
{
	msgComp comp;
	m_sendQ = make_shared<std::priority_queue<msgElement, std::vector<msgElement>, msgComp>>(comp);
	m_recvQ = make_shared<std::priority_queue<msgElement, std::vector<msgElement>, msgComp>>(comp);
}

TetrisSocket::~TetrisSocket()
{
	while(!m_recvQ->empty())
	{
		auto msg = m_recvQ->top();
		m_recvQ->pop();
		delete[] msgHelper::getMessage(msg);
	}
	while(!m_sendQ->empty())
	{
		auto msg = m_sendQ->top();
		m_recvQ->pop();
		delete[] msgHelper::getMessage(msg);
	}
}

void TetrisSocket::SetIP(IPString &ip)
{
	m_ip = ip;
}

void TetrisSocket::SetPort(portType port)
{
	m_port = port;
}

int TetrisSocket::accept()
{
	_runAcception();

	return 0u;
}

unsigned TetrisSocket::connect()
{
	auto err = 0u;
	if((err = _connect()) > 0)
		return err;
	_run();
	
	return 0u;
}

void TetrisSocket::readnwrite()
{
	_run();
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

	const auto popfn = &TetrisSocket::_popMessage;
	m_popThread = make_shared<std::thread>(popfn, this);
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
		if(!m_sendQ->empty())
		{
			auto msg = m_sendQ->top();
			m_sendQ->pop();
			
			const auto realMsg = msgHelper::getMessage(msg);
			const auto size = msgHelper::getSize(msg);

			const auto written = _sendTo(realMsg, size);
			if(written <= 0)
			{
				m_closeSocket = false;
				//writeLog("error sendto");
			}

			delete[] realMsg;
		}
	}
}

void TetrisSocket::_recv()
{
	while(m_closeSocket)
	{
		auto msg = _recvFrom();
		if(msgHelper::getSize(msg) <= 0)
		{
			m_closeSocket = false;
			//writeLog("error recvfrom");
			break;
		}
		m_recvQ->push(msg);
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

void TetrisSocket::_popMessage()
{
	while(true)
	{
		if(!m_recvQ->empty())
		{
			auto msg = m_recvQ->top();
			m_recvQ->pop();

			const auto message = msgHelper::getMessage(msg);

			auto msgptr = shared_ptr<const char>(message,
				[](const char* msg){delete[] msg; });

			switchingMessage(msg);
		}
	}
}
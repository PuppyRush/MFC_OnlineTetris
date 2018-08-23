#include "TSocket.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif

using namespace std;

TetrisSocket::TetrisSocket(const int domain, const int type, const int protocol, const IPString ip, const tetris::t_port port)
	:TMessenger(),
	m_closeSocket(true),
	m_domain(domain),
	m_type(type),
	m_protocol(protocol),
	m_port(port),
	m_ip(ip),
	m_socket(0)
{
	msgComp comp;
	m_sendQ = priority_queue<tetris::msgElement, vector<tetris::msgElement>, msgComp>(comp);
	m_recvQ = priority_queue<tetris::msgElement, vector<tetris::msgElement>, msgComp>(comp);
}

TetrisSocket::TetrisSocket(const int domain, const int type, const int protocol, tetris::t_socket socket)
	:TMessenger(),
	m_closeSocket(true),
	m_domain(domain),
	m_type(type),
	m_protocol(protocol),
	m_socket(socket)
{
}

TetrisSocket::~TetrisSocket()
{
	while (!m_recvQ.empty())
	{
		auto msg = m_recvQ.top();
		m_recvQ.pop();
		delete[] msgHelper::getMessage(msg);
	}
	while (!m_sendQ.empty())
	{
		auto msg = m_sendQ.top();
		m_recvQ.pop();
		delete[] msgHelper::getMessage(msg);
	}
}

void TetrisSocket::setIP(IPString &ip)
{
	m_ip = ip;
}

void TetrisSocket::setPort(tetris::t_port port)
{
	m_port = port;
}

tetris::t_socket TetrisSocket::popSocket()
{
	while (true)
	{
		if (!m_acceptedSocketQ.empty())
		{
			const unsigned socket = m_acceptedSocketQ.front();
			m_acceptedSocketQ.pop();
			return socket;
		}
	}
}

tetris::t_error TetrisSocket::accept()
{
	_runAcception();


	return 0u;
}

tetris::t_error TetrisSocket::connect()
{
	return _connect();
}

tetris::t_error TetrisSocket::close()
{
	_end();
	return _close(m_socket);
}

void TetrisSocket::_runAcception()
{
	const auto acceptFn = &TetrisSocket::_acceptSocket;
	m_acceptThread = make_shared<thread>(acceptFn, this);
}

void TetrisSocket::_end()
{
	m_closeSocket = false;
}

void TetrisSocket::send()
{
	if (!m_sendQ.empty())
	{
		auto msg = m_sendQ.top();
		m_sendQ.pop();

		const auto realMsg = msgHelper::getMessage(msg);
		const auto size = msgHelper::getSize(msg);

		const auto written = _sendTo(realMsg, size);
		if (written <= 0)
		{
			//writeLog("error sendto");
		}

		delete[] realMsg;
	}
}

const tetris::msgElement TetrisSocket::recv()
{
	auto msg = _recvFrom();
	if (msgHelper::getSize(msg) <= 0)
	{
		//writeLog("error recvfrom");
	}
	else
		return msg;
}


void TetrisSocket::_acceptSocket()
{
	while (m_closeSocket)
	{
		volatile const int socket = _accept();
		if (socket == -1)
		{
			;//writeLog("error recvfrom");
		}
		else
		{
			m_acceptedSocketQ.push(socket);
		}
	}
}

//void TetrisSocket::_popMessage()
//{
//	if (!m_recvQ.empty())
//	{
//		auto msg = m_recvQ->top();
//		m_recvQ->pop();
//
//		const auto message = msgHelper::getMessage(msg);
//
//		switchingMessage(msg);
//		delete[] msgHelper::getMessage(msg);
//	}
//}

char* TetrisSocket::getBuffer()
{
	try
	{
		char* msg = new char[PACKET_LEN];
		//assert(msg != NULL);
		memset(msg, 0, PACKET_LEN);
		return msg;
	}
	catch (exception e)
	{
		static char* emptyMsg = new char[0];
		return emptyMsg;
	}
}

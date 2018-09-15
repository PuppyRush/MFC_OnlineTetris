#include "stdafx.h"
#include "SocketImpl.h"
#include "../Commons/TMessageThread.h"

SocketImpl::SocketImpl(const int domain, const int type, const int protocol, const IPString ip, const tetris::t_port port)
	:TetrisSocket(domain, type, protocol,ip,port)
{
}

SocketImpl::~SocketImpl()
{
	if(!m_closeSocket)
		_close(getSocket());
	m_closeSocket = false;

	while(!m_acceptedSocketQ.empty())
	{
		const auto socket = m_acceptedSocketQ.front();
		m_acceptedSocketQ.pop();
		_close(socket);
	}
}

tetris::t_error SocketImpl::create(IPString ip, tetris::t_port port)
{
	m_ip = ip;
	m_port = port;
	setSocket(socket(m_domain, m_type, m_protocol));

	struct sockaddr_in SockInfo;

	SockInfo.sin_family = AF_INET;
	SockInfo.sin_port = htons(m_port);
	SockInfo.sin_addr.s_addr = htonl(INADDR_ANY);

	tetris::t_error err = 0;
	err = ::bind(getSocket(), (struct sockaddr*)&SockInfo, sizeof(struct sockaddr_in));
	if (err == 0)
	{
		return this->connect();
	}
	else
		return err;
}

tetris::t_error SocketImpl::_connect()
{
	sockaddr_in addr;

	memset((void *)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(m_ip.GetString());
	addr.sin_port = htons(m_port);

	int res = 0;
	if ((res = ::connect(getSocket(), (sockaddr *)&addr, sizeof(sockaddr_in))) == 0)
	{
		auto socketThread = TMessageThread::get();
		socketThread->run();
		return tetris::t_error(0);
	}
	else
		return res;
}

tetris::t_error SocketImpl::_close(unsigned _socket)
{
	return ::closesocket(_socket);
}

const size_t SocketImpl::_sendTo(const char *msg, const size_t size)
{
	return ::send(getSocket(), msg, size,0);
}

const TMessageObject SocketImpl::_recvFrom()
{
	auto buf = new char[PACKET_LEN];
	memset(buf, 0, PACKET_LEN);
	int recved = ::recv(getSocket(), const_cast<char *>(buf), PACKET_LEN, 0);
	const tetris::t_msgsize recvLen = recved <= 0 ? 0u : recved;
	
	return TMessageObject::toMessage(getSocket(), buf, recvLen);
}
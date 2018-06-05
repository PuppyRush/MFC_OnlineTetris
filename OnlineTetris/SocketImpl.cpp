#include "stdafx.h"
#include "SocketImpl.h"

SocketImpl::SocketImpl(const int domain, const int type, const int protocol)
	:TetrisSocket(domain, type, protocol)
{
}

SocketImpl::~SocketImpl()
{
	if(!m_closeSocket)
		_close(m_socket);
	m_closeSocket = false;

	while(!m_acceptedSocketQ.empty())
	{
		const auto socket = m_acceptedSocketQ.front();
		m_acceptedSocketQ.pop();
		_close(socket);
	}
}

unsigned SocketImpl::create(const IPString ip, const unsigned port)
{
	m_ip = ip;
	m_port = port;

	m_socket = socket(m_domain, m_type, m_protocol);

	struct sockaddr_in SockInfo;

	SockInfo.sin_family = AF_INET;
	SockInfo.sin_port = htons(port);
	SockInfo.sin_addr.s_addr = htonl(INADDR_ANY);

	return ::bind(m_socket, (struct sockaddr*)&SockInfo, sizeof(struct sockaddr_in));
}

unsigned SocketImpl::_connect()
{
	sockaddr_in addr;

	memset((void *)&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(m_ip.GetString());
	addr.sin_port = htons(m_port);

	return ::connect(m_socket, (sockaddr *)&addr, sizeof(sockaddr_in));
}

unsigned SocketImpl::_close(unsigned _socket)
{
	return ::closesocket(_socket);
}

const size_t SocketImpl::_sendTo(const char *msg, const size_t size)
{
	return ::send(m_socket, msg, size,0);
}

pair<const char* , const size_t> SocketImpl::_recvFrom()
{
	auto buf = getBuffer();
	const size_t recvLen =	::recv(m_socket, const_cast<char *>(buf), PACKET_LEN,0);

	return make_pair(buf, recvLen);
}
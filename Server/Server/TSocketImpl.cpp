#include "TSocketImpl.h"

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include <numeric>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TSocketImpl::TSocketImpl(const int domain, const int type, const int protocol, const IPString ip, const tetris::t_port port)
	:TetrisSocket(domain, type, protocol, ip, port)
{
}

TSocketImpl::TSocketImpl(const int domain, const int type, const int protocol, tetris::t_socket socket)
	: TetrisSocket(domain, type, protocol, socket)
{}

tetris::t_error TSocketImpl::listen(const unsigned port, int backlog)
{
	setSocket(::socket(m_domain, m_type, m_protocol));

	struct sockaddr_in SockInfo;

	SockInfo.sin_family = AF_INET;
	SockInfo.sin_port = htons(port);
	SockInfo.sin_addr.s_addr = htonl(INADDR_ANY);

	if (::bind(getSocket(), (struct sockaddr*)&SockInfo, sizeof(struct sockaddr_in)) == 0)
		return ::listen(getSocket(), backlog) == 0;
	else
		return -1;
}

volatile tetris::t_socket TSocketImpl::_accept()
{
	struct sockaddr_in cliaddr;
	unsigned addrlen = sizeof(cliaddr);
	int accepted_socket = ::accept(getSocket(), reinterpret_cast<struct sockaddr *>(&cliaddr), &addrlen);
	if (accepted_socket < 0)
	{
		return std::numeric_limits<tetris::t_socket>::max();
	}
	return static_cast<tetris::t_socket>(accepted_socket);
}

tetris::t_error TSocketImpl::_close(const unsigned _socket)
{
	return ::close(_socket);
}

const size_t TSocketImpl::_sendTo(const char *msg, const size_t size)
{
	return ::send(getSocket(), msg, size, 0);
}

const TMessageObject TSocketImpl::_recvFrom()
{
	//auto buf = getBuffer();
	auto buf = new char[PACKET_LEN];
	memset(buf, 0, PACKET_LEN);
	
	int recved = ::recv(getSocket(), const_cast<char *>(buf), PACKET_LEN, 0);
	const tetris::t_msgsize recvLen = recved <= 0 ? 0u : recved;
	auto prio = Header::getPriority(buf);

	return TMessageObject::toMessage(getSocket(), buf,recvLen);
}

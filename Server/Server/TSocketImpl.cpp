#include "TSocketImpl.h"

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


TSocketImpl::TSocketImpl(const int domain, const int type, const int protocol)
	:TetrisSocket(domain, type, protocol)
{
}

int TSocketImpl::listen(const unsigned port, int backlog)
{
	m_socket = ::socket(m_domain, m_type, m_protocol);

	struct sockaddr_in SockInfo;

	SockInfo.sin_family = AF_INET;
	SockInfo.sin_port = htons(port);
	SockInfo.sin_addr.s_addr = htonl(INADDR_ANY);

	if(::bind(m_socket, (struct sockaddr*)&SockInfo, sizeof(struct sockaddr_in))==0)
		return ::listen(m_socket, backlog)==0;
	else
		return -1;
}

int TSocketImpl::_accept()
{
	struct sockaddr_in cliaddr;
	unsigned addrlen = sizeof(cliaddr);
	auto accepted_socket = ::accept(m_socket, reinterpret_cast<struct sockaddr *>(&cliaddr), &addrlen);
	if(accepted_socket < 0)
	{
		perror("accept fail");
		//exit(0);
		return -1;
	}
	return accepted_socket;
}

unsigned TSocketImpl::_close(const unsigned _socket)
{
	return ::close(_socket);
}

const size_t TSocketImpl::_sendTo(const char *msg, const size_t size)
{
	return ::send(m_socket, msg, size,0);
}


msgElement TSocketImpl::_recvFrom()
{
	auto buf = getBuffer();
	const size_t recvLen =	::read(m_socket, const_cast<char *>(buf), 512);

	return make_pair(static_cast<const char*>(buf), recvLen);
}


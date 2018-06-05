#include "SocketImpl.h"

SocketImpl::SocketImpl(const int domain, const int type, const int protocol)
	:TetrisSocket(domain, type, protocol)
{
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

int SocketImpl::_accept()
{

	struct sockaddr_in cliaddr;
	const auto addrlen = sizeof(cliaddr);
	auto accepted_socket = ::accept(m_socket, reinterpret_cast<struct sockaddr *>(&cliaddr), &addrlen);
	if(accepted_socket < 0)
	{
		perror("accept fail");
		//exit(0);
	}

}

unsigned SocketImpl::_close()
{
	return ::close(m_socket);
}

const size_t SocketImpl::_sendTo(const char *msg, const size_t size)
{
	return ::send(m_socket, msg, size,0);
}


pair<const char* , const size_t> SocketImpl::_recvFrom()
{
	auto buf = getBuffer();
	const size_t recvLen =	::read(m_socket, const_cast<char *>(buf), defineinfo::PACKET_LEN);

	return make_pair(buf, recvLen);
}


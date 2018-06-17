#include "stdafx.h"
#include "SocketImpl.h"

SocketImpl::SocketImpl(const int domain, const int type, const int protocol, const IPString ip, const t_port port)
	:TetrisSocket(domain, type, protocol,ip,port)
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

unsigned SocketImpl::create(IPString ip, t_port port)
{
	m_ip = ip;
	m_port = port;
	m_socket = socket(m_domain, m_type, m_protocol);

	struct sockaddr_in SockInfo;

	SockInfo.sin_family = AF_INET;
	SockInfo.sin_port = htons(m_port);
	SockInfo.sin_addr.s_addr = htonl(INADDR_ANY);

	::bind(m_socket, (struct sockaddr*)&SockInfo, sizeof(struct sockaddr_in));

	if(connect() == 0)
	{
		const auto me = TUserClient::GetMe();
		const auto header = Header(toUType(SERVER_MSG::ON_CONNECTION_INFO));
		const mSendName sendname(header, me->GetUserName().size(), me->GetUserName().c_str());
		pushMessage(&sendname);
		return true;
	}
	else
		return false;
}

unsigned SocketImpl::_connect()
{
	sockaddr_in addr;

	memset((void *)&addr, 0, sizeof(addr));
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

msgElement SocketImpl::_recvFrom()
{
	auto buf = getBuffer();
	const size_t recvLen =	::recv(m_socket, const_cast<char *>(buf), PACKET_LEN,0);
	auto prio = Header::getPriorty(buf);

	return msgHelper::getMsgElement(prio, buf, recvLen);
}
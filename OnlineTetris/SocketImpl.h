#pragma once

#include <winsock.h>

#include "../Commons/TSocket.h"
#include "../Commons/TType.h"

using namespace tetris;

class SocketImpl : public TetrisSocket
{
public:
	
	virtual ~SocketImpl();

	virtual unsigned create(IPString ip, t_port port) override;
	
	virtual int listen(unsigned port, int backlog) {return 0;}

protected:
	explicit SocketImpl(const int domain, const int type, const int protocol, const IPString ip, const t_port port);

	virtual int _accept() override
	{
		return 0;
	}

	virtual unsigned _connect() override;
	virtual int _close(unsigned _socket) override;

	virtual const size_t _sendTo(const char *msg, const size_t size) override;
	virtual msgElement _recvFrom() override;

};
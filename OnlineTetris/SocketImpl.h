#pragma once

#include <winsock.h>

#include "../Commons/TSocket.h"
#include "../Commons/TType.h"

class SocketImpl : public TetrisSocket
{
public:
	
	virtual ~SocketImpl();

	virtual tetris::t_error create(IPString ip, tetris::t_port port) override;
	virtual tetris::t_error listen(unsigned port, int backlog) {return 0;}

protected:
	explicit SocketImpl(const int domain, const int type, const int protocol, const IPString ip, const tetris::t_port port);

	virtual volatile int _accept() override
	{
		return 0;
	}

	virtual tetris::t_error _connect() override;
	virtual tetris::t_error _close(unsigned _socket) override;

	virtual const size_t _sendTo(const char *msg, const size_t size) override;
	virtual tetris::msgElement _recvFrom() override;

};
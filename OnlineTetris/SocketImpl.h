#pragma once

#include <winsock.h>

#include "../Commons/TetrisSocket.h"

using namespace tetris_socket;

class SocketImpl : public TetrisSocket
{

public:
	explicit SocketImpl(const int domain, const int type, const int protocol);
	~SocketImpl();

	virtual unsigned create(const IPString ip, const unsigned port) override;
	
	virtual unsigned listen() {return 0;}
	virtual unsigned accept() {return 0;}

protected:

	virtual int _accept() override
	{
		return 0;
	}

	virtual unsigned _connect() override;
	virtual unsigned _close(unsigned _socket) override;


	virtual const size_t _sendTo(const char *msg, const size_t size) override;
	virtual pair<const char*, const size_t> _recvFrom() override;

};
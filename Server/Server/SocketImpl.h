#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "DefineInfo.h"
#include "TetrisSocket.h"

using namespace tetris_socket;

class SocketImpl : public TetrisSocket
{

public:

	explicit SocketImpl(const int domain, const int type, const int protocol);

	virtual unsigned create(const IPString ip, const unsigned port) override;
	
	virtual unsigned accept() override;

protected:

	virtual int _accept() override

	virtual unsigned _connect() override
	{
		return 0;
	}

	virtual unsigned _close() override;

	virtual const size_t _sendTo(const char *msg, const size_t size) override;
	virtual pair<const char*, const size_t> _recvFrom() override;

private:
	unsigned m_socket;
};

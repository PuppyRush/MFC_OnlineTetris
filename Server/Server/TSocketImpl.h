#pragma once

#include "DefineInfo.h"
#include "TetrisSocket.h"


class TSocketImpl : public tetris_socket::TetrisSocket
{

public:
	TSocketImpl() = delete;
	explicit TSocketImpl(const int domain, const int type, const int protocol);
	virtual ~TSocketImpl(){}

	virtual unsigned create(const IPString ip, const unsigned port) override {}
	virtual int listen(const unsigned port, int backlog) override;

protected:

	virtual int _accept() override;
	virtual unsigned _close(const unsigned _socket) override;
	virtual unsigned _connect() override 	{return 0;};

	virtual const size_t _sendTo(const char *msg, const size_t size) override;
	virtual pair<const char*, const size_t> _recvFrom() override;


};


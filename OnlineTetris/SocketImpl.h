#pragma once

#include <winsock.h>

#include "../Commons/Entity/TSocket.h"
#include "../Commons/TType.h"
#include "../Commons/TProperty.h"
#include "../Commons/TMessageObject.h"


class SocketImpl : public TetrisSocket
{
public:
	
	virtual ~SocketImpl();

	virtual tetris::t_error create(IPString ip, tetris::t_port port) override;
	virtual tetris::t_error listen(unsigned port, int backlog) {return 0;}

protected:
	explicit SocketImpl(const int domain, const int type, const int protocol, const IPString ip, const tetris::t_port port);

	virtual volatile tetris::t_error _accept() override
	{
		return toUType(property_error::eFail);
	}

	virtual tetris::t_error _connect() override;
	virtual tetris::t_error _close(unsigned _socket) override;

	virtual const size_t _sendTo(const char *msg, const size_t size) override;
	virtual const TMessageObject _recvFrom() override;

};
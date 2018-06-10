/*
 * ServerSocket.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */
#pragma once

#include "TSocketImpl.h"
#include "TType.h"

class TServerSocket : public TSocketImpl
{
	using namespace tetris_socket;
	using namespace tetris_type;
public:
	TServerSocket();
	explicit TServerSocket(const unsigned socket);
	virtual ~TServerSocket();

	static shared_ptr<TServerSocket> makeShared(const unsigned socket, const tUnique unique)
	{
		auto serversocket = make_shared<TServerSocket>(socket,unique);
		serversocket->readnwrite();
		return serversocket;
	}

protected:
	virtual unsigned _close(const unsigned _socket) override;

};


/*
 * ServerSocket.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */
#pragma once

#include "TSocketImpl.h"

using namespace tetris_socket;

class TServerSocket : public TSocketImpl
{

public:
	TServerSocket();
	explicit TServerSocket(const unsigned socket);
	virtual ~TServerSocket();

	static shared_ptr<TServerSocket> makeShared(const unsigned socket)
	{
		auto serversocket = make_shared<TServerSocket>(socket);
		serversocket->readnwrite();
		return serversocket;

	}

protected:
	virtual unsigned _close(const unsigned _socket) override;

};


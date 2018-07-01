/*
 * ServerSocket.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */
#pragma once

#include "../../Commons/TType.h"

#include "../Room/TWaitingRoom.h"
#include "TSocketImpl.h"


class TServerSocket : public TSocketImpl
{
public:
	TServerSocket();
	explicit TServerSocket(tetris::t_socket socekt);
	virtual ~TServerSocket();

	static shared_ptr<TServerSocket> makeShared(const unsigned socket)
	{
		auto serversocket = make_shared<TServerSocket>(socket);
		serversocket->readnwrite();
		return serversocket;
	}

	virtual void switchingMessage(const tetris::msgElement &msg);

private:

	void recvConnectionInfo(const tetris::msgElement &msg);
	void sendConnectionInfo();
};

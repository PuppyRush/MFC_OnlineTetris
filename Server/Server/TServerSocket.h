/*
 * ServerSocket.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */
#pragma once

#include <memory>

#include "../../Commons/TType.h"
#include "../Room/TWaitingRoom.h"
#include "TSocketImpl.h"
#include "TMessageObject.h"

class TServerSocket : public TSocketImpl
{
public:
	TServerSocket();
	virtual ~TServerSocket();

	virtual void registryMessage() override;


	inline static std::shared_ptr<TServerSocket> makeShared()
	{
		return std::shared_ptr<TServerSocket>(new TServerSocket());
	}

	inline static std::shared_ptr<TServerSocket> makeShared(const unsigned socket)
	{
		return std::shared_ptr<TServerSocket>(new TServerSocket(socket));
	}

	void sendConnectionInfo();

private:

	explicit TServerSocket(tetris::t_socket socekt);
	void recvConnectionInfo(const TMessageObject& msg);
};

/*
 * TetrisUserServer.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <atomic>

#include "../../Commons/Entity/TUser.h"
#include "../../Commons/TType.h"
#include "TServerSocket.h"
#include "TMessageObject.h"


class TServerUser : public TetrisUser
{
public:
	virtual ~TServerUser();
	virtual void registryMessage() override;

	static tetris::t_ptr<TServerUser> get(const tetris::t_socket socket)
	{
		static auto me = std::shared_ptr<TServerUser>(new TServerUser(socket));
		return me;
	}

	static tetris::t_ptr<TServerUser> makeShared(const tetris::t_socket socket)
	{
		return tetris::t_ptr<TServerUser>(new TServerUser(socket));
	}

protected:
    TServerUser(const tetris::t_socket socket);

private:

	void recvConnectionInfo(const TMessageObject& msg);
	void recvChatMessage(const TMessageObject& msg);
};

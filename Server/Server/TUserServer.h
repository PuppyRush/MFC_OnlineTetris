/*
 * TetrisUserServer.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <atomic>

#include "TetrisUser.h"
#include "TServerSocket.h"
#include "TType.h"
class TUserServer : public TetrisUser
{
	using namespace tetris_Type;

public:

	TUserServer(const std::shared_ptr<TServerSocket> &socket, const tetris_Type::tUnique unique);
	virtual ~TUserServer();

	static std::shared_ptr<TUserServer> makeShared(const std::shared_ptr<TServerSocket> &socket)
	{
		return std::make_shared<TUserServer>(socket);
	}

	shared_ptr<TServerSocket> m_socket;
	
	virtual void switchingMessage(const msg_element &msg);

protected:


private:
	const tUnique m_unique;
	
	void recvmsg(msg_element &msg);
};



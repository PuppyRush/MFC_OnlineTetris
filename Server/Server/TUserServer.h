/*
 * TetrisUserServer.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include "TetrisUser.h"
#include "TServerSocket.h"

class TUserServer : public TetrisUser
{

public:

	TUserServer(const std::shared_ptr<TServerSocket> &socket);
	virtual ~TUserServer();

	static std::shared_ptr<TUserServer> makeShared(const std::shared_ptr<TServerSocket> &socket)
	{
		return std::make_shared<TUserServer>(socket);
	}

	shared_ptr<TServerSocket> m_socket;

protected:


private:


};



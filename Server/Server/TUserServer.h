/*
 * TetrisUserServer.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <atomic>

#include "../../Commons/TUser.h"
#include "../../Commons/TType.h"
#include "TServerSocket.h"

using namespace std;

class TUserServer : public TetrisUser
{
public:
	TUserServer(const std::shared_ptr<TServerSocket> &socket, const t_unique unique);
	virtual ~TUserServer();

	static std::shared_ptr<TUserServer> makeShared(const std::shared_ptr<TServerSocket> &socket, 
		const t_unique unique)
	{
		return std::make_shared<TUserServer>(socket,unique);
	}

	shared_ptr<TServerSocket> m_socket;
	
protected:


private:
	const t_unique m_unique;
};



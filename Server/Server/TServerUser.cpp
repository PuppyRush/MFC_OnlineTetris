/*
 * TetrisUserServer.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <string>
#include <sys/socket.h>

#include "../../Commons/TMessage.h"
#include "../../Commons/Entity/TSocket.h"
#include "TServerUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TServerUser::TServerUser(const tetris::t_userUnique unique, const std::shared_ptr<TServerSocket> socket)
	:TetrisUser(unique),
	m_serverSocket(socket),
	m_sharedPtr(std::shared_ptr<TServerUser>(this))
{
    registryMessage();
}

TServerUser::TServerUser(TServerUser* user)
	:TetrisUser(user->getUnique())
{
    registryMessage();
}

TServerUser::~TServerUser()
{
	// TODO Auto-generated destructor stub
}

void TServerUser::registryMessage()
{
    this->addCaller(make_pair(toUType(SERVER_MSG::CONNECTION_INFO), std::bind(&TServerUser::recvConnectionInfo, this, std::placeholders::_1)));
}


void TServerUser::recvConnectionInfo(const tetris::msgElement &msg)
{
	const auto message = toMessage<mName>(msg);
	setName(message.name);
}


/*
 * TetrisUserServer.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <string>
#include <sys/socket.h>

#include "../../Commons/TMessageStruct.h"
#include "../../Commons/Entity/TSocket.h"
#include "../../Commons/TObjectContainerFactory.h"
#include "TServerUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TServerUser::TServerUser(const tetris::t_socket socket)
    :TetrisUser(socket)
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


void TServerUser::recvConnectionInfo(const TMessageObject& msg)
{
	const auto message = TMessageObject::toMessage<mName>(msg);
	if(message.unique != this->getUnique())
	    return;

	setName(message.name);

    auto waitroomcon = TObjectContainerFactory::get()->getContainer<TIWaitingRoom>(property_distinguish::WaitingRoom);
    auto waitingRoom = dynamic_cast<TWaitingRoom*>(*waitroomcon->begin());
    waitingRoom->sendWaitingUsers(this->getSocket());
}


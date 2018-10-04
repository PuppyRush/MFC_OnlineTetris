/*
 * ServerManager.cpp
 *
 *  Created on: 2018. 2. 11.
 *      Author: cmk
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>
#include <thread>

#include "TServerManager.h"
#include "TServerUser.h"
#include "TMessageThread.h"
#include "../Room/TWaitingRoom.h"
#include "../../Commons/TMessageSender.h"
#include "../../Commons/Entity/TSocket.h"
#include "../../Commons/TMessageStruct.h"
#include "../../Commons/TObjectContainerFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

TServerManager::TServerManager()
	:m_closedServer(true)
{
	// TODO Auto-generated constructor stub
	m_mainServerSocket = TServerSocket::get();
	_makeWaitingRoom();
}

TServerManager::~TServerManager()
{
	// TODO Auto-generated destructor stub
}


void TServerManager::_makeWaitingRoom()
{
	auto admin = TServerUser::get(this->m_mainServerSocket->getSocket());
	admin->setName("admin");

	TObjectContainerFactory::get()->getContainer<TetrisUser>()->add(admin);

	RoomInfo room(-1,0,"Tetris1",0, toUType(TWaitingRoom::property::MaxSize),0);
	auto basicWaitingRoom = TWaitingRoom::makeShared(room);
	basicWaitingRoom->enter(UserInfo(admin->getUnique(), admin->getUserName().c_str()));

	auto waitroomcon = TObjectContainerFactory::get()->getContainer<TIWaitingRoom>();
	waitroomcon->add(basicWaitingRoom);
}

void TServerManager::beginServer()
{
	if (m_mainServerSocket->listen(5905u, 100))
	{
		if (m_mainServerSocket->accept() == 0)
		{
			auto socketThread = TMessageThread::get();
			socketThread->run();

			const auto runfn = &TServerManager::run;
			m_severManagerThread = std::make_shared<std::thread>(runfn, this);
			m_severManagerThread->join();
		}
	}
}

void TServerManager::run()
{
	while (m_closedServer)
	{
		auto socketUnique = m_mainServerSocket->popSocket();
		_HelloUser(socketUnique);
	}
}


void TServerManager::_HelloUser(const tetris::t_socket socketUnique)
{
	auto newsocket = TServerSocket::makeShared(socketUnique);
	auto newUser = TServerUser::makeShared(newsocket->getSocket());

	auto waitroomcon = TObjectContainerFactory::get()->getContainer<TIWaitingRoom>();
	auto waitingRoom = dynamic_cast<TWaitingRoom*>(*waitroomcon->begin());

	waitingRoom->enter( UserInfo(newUser->getUnique(), newUser->getUserName().c_str() ));
	TObjectContainerFactory::get()->getContainer<TetrisUser>()->add(newUser);
	TObjectContainerFactory::get()->getContainer<TetrisSocket>()->add(newsocket);

    const auto header = Header( toUType(Priority::High), toUType(SERVER_MSG::CONNECTION_INFO));
    mConnectionInfo msg(header, newUser->getUnique());

    TMessageSender::get()->push( TMessageObject::toMessage(socketUnique, &msg));

	waitingRoom->sendWaitingRooms(socketUnique);
	TWaitingRoom::sendWaitingRoomInfo(socketUnique);


}
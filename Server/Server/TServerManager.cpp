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
}

TServerManager::~TServerManager()
{
	// TODO Auto-generated destructor stub
}

void TServerManager::beginServer()
{
	if (m_mainServerSocket->listen(5905u, 100))
	{
		if (m_mainServerSocket->accept() == 0)
		{
			makeWaitingRoom();

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
		std::lock_guard<std::mutex> lck(m_mutex);

		auto socketUnique = m_mainServerSocket->popSocket();
		HelloUser(socketUnique);

#ifdef _DEBUG
		printf("hello new socket : %d\n",socketUnique);
#endif

	}
}

void TServerManager::makeWaitingRoom()
{
    auto admin = TServerUser::get(this->m_mainServerSocket->getSocket());
    admin->setName("admin");

    TObjectContainerFactory::get()->getContainer<TetrisUser>(property_distinguish::User)
            ->add(admin);

	RoomInfo room(-1,0,"Tetris1",0, toUType(TWaitingRoom::property::Size),0);
	auto waitingRoom = TWaitingRoom::makeShared(room);
    waitingRoom->add(*admin);

    auto waitroomcon = TObjectContainerFactory::get()->getContainer<TIWaitingRoom>(property_distinguish::WaitingRoom);
    waitroomcon->add(waitingRoom);
}

void TServerManager::HelloUser(const tetris::t_socket socketUnique)
{
	auto newsocket = TServerSocket::makeShared(socketUnique);
	auto newUser = TServerUser::makeShared(newsocket->getSocket());

	auto waitroomcon = TObjectContainerFactory::get()->getContainer<TIWaitingRoom>(property_distinguish::WaitingRoom);
	auto waitingRoom = dynamic_cast<TWaitingRoom*>(*waitroomcon->begin());


	waitingRoom->add(*newUser.get());
	TObjectContainerFactory::get()->getContainer<TetrisUser>(property_distinguish::User)->add(newUser);
	TObjectContainerFactory::get()->getContainer<TetrisSocket>(property_distinguish::Socket)->add(newsocket);

    const auto header = Header( toUType(Priority::High), toUType(SERVER_MSG::CONNECTION_INFO));
    mConnectionInfo msg(header, newUser->getUnique());

    TMessageSender::get()->push( TMessageObject::toMessage(socketUnique, &msg));

	waitingRoom->sendWaitingRooms(socketUnique);


}
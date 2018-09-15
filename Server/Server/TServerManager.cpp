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

TServerManager::TServerManager()
	:m_closedServer(true)
{
	// TODO Auto-generated constructor stub
	m_mainServerSocket = TServerSocket::makeShared();
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
	auto waitingRoom = TWaitingRoom::getWaitingRoom();
	TObjectContainerFactory::get()->getContainer<TIWaitingRoom>(property_distinguish::WaitingRoom)->add(waitingRoom);
}

void TServerManager::HelloUser(const tetris::t_socket socketUnique)
{
	auto newsocket = TServerSocket::makeShared(socketUnique);
	auto newUser = TServerUser::makeShared(newsocket);
    auto waitingRoom = TObjectContainerFactory::get()->getContainer<TIWaitingRoom>(property_distinguish::WaitingRoom)->begin();

	waitingRoom->add(newUser->getUnique());
	TObjectContainerFactory::get()->getContainer<TetrisUser>(property_distinguish::User)->add(newUser);
	TObjectContainerFactory::get()->getContainer<TetrisSocket>(property_distinguish::Socket)->add(newsocket);

    const auto header = Header( toUType(Priority::High), toUType(SERVER_MSG::CONNECTION_INFO));
    mConnectionInfo msg(header, newUser->getUnique());

    TMessageSender::get()->push( TMessageObject::toMessage(socketUnique, &msg));


    const auto userinfo = TWaitingRoom::getWaitingRoom()->getUserInfo();
    const size_t size = userinfo.size();
    UserInfo* userinfoAry = new UserInfo[size];

    const auto routine = size/USER_SIZE+1;
    size_t accu=0;
    for(size_t i=0 ; i < routine ; i++)
    {
		for (size_t l = 0; l < USER_SIZE && l < userinfo.size() ; l++)
			userinfoAry[l] = UserInfo(userinfo.at(l+accu).userUnique, userinfo.at(l+accu).name);
		accu += userinfo.size();

		const auto header2 = Header( toUType(Priority::Normal), toUType(SERVER_MSG::WAITINGROOM_INFO));
		mWaitingRoomInfo waitingroom_msg(header2, waitingRoom->getUnique() ,userinfoAry, size);

		TMessageSender::get()->push( TMessageObject::toMessage(socketUnique,&waitingroom_msg));
	}


    const auto roominfo = TWaitingRoom::getWaitingRoom()->getUserInfo();
    const size_t totalRoomsize = roominfo.size();
    auto roominfoAry = new RoomInfo[totalRoomsize];

    const auto routine = size/ROOM_SIZE+1;
    accu=0;
    for(size_t i=0 ; i < routine ; i++)
    {
        for (size_t l = 0; l < ROOM_SIZE && l < roominfo.size() ; l++)
            roominfoAry[l] = RoomInfo(roominfo);
        accu += totalRoomsize;

        const auto header2 = Header( toUType(Priority::High), toUType(SERVER_MSG::WAITINGROOM_USER));
        mWaitingUserInfo waitinguser_msg(header2, waitingRoom->getUnique() ,roominfoAry, totalRoomsize);

        TMessageSender::get()->push( TMessageObject::toMessage(socketUnique,&waitinguser_msg));
    }

	delete[] userinfoAry;
}
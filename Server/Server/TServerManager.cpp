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
#include "../../Commons/MessageHeader.h"
#include "../../Commons/TSocketThread.h"
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

TServerManager::~TServerManager() {
	// TODO Auto-generated destructor stub
}

void TServerManager::beginServer()
{
	auto serverSocket = make_shared<TServerSocket>();
	if (serverSocket->listen(5905u, 100))
	{
		if (serverSocket->accept() == 0)
		{
			auto socketThread = TSocketThread::get();
			socketThread->run();

			const auto runfn = &TServerManager::run;
			m_severManagerThread = make_shared<thread>(runfn, this);
			m_severManagerThread->join();
		}
	}
}

void TServerManager::run()
{
	while (m_closedServer)
	{
		lock_guard<mutex> lck(m_mutex);

		auto socketUnique = m_mainServerSocket->popSocket();
		auto socket = TServerSocket::makeShared(socketUnique);
		
		auto newUser = TServerUser::makeShared();

		TObjectContainerFactory::get()->getSocketContainer()->add(socketUnique,socket);
		TObjectContainerFactory::get()->getUserContainer()->add(newUser->getUnique(), newUser);

	}
}

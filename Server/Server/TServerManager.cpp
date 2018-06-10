/*
 * ServerManager.cpp
 *
 *  Created on: 2018. 2. 11.
 *      Author: cmk
 */

#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>
#include "TServerManager.h"
#include "MessageHeader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

TServerManager::TServerManager(const shared_ptr<TServerSocket> &socket)
:m_mainServerSocket(socket),
m_unique()
{
	// TODO Auto-generated constructor stub
}

TServerManager::~TServerManager() {
	// TODO Auto-generated destructor stub
}

void TServerManager::BeginServer()
{
	const auto runfn = &TServerManager::run;
	m_severManagerThread = std::make_shared<std::thread>(runfn, this);
	m_severManagerThread->join();
}

void TServerManager::run()
{
	while(1)
	{
		auto newClientSocket = m_mainServerSocket->popSocket();

		std::lock_guard<std::mutex> lck (m_mutex);

		auto serverSocket = TServerSocket::makeShared(newClientSocket);
		auto newUser = TUserServer::makeShared(serverSocket, getUnique());
		newUser->run();
		
		m_connectionPool.emplace_back(newUser);
	}
}

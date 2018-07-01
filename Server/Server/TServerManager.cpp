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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TServerManager::TServerManager(shared_ptr<TServerSocket> &socket)
	:m_mainServerSocket(socket),
	m_closedServer(true)
{
	// TODO Auto-generated constructor stub
}

TServerManager::~TServerManager() {
	// TODO Auto-generated destructor stub
}

void TServerManager::beginServer()
{
	const auto runfn = &TServerManager::run;
	m_severManagerThread = make_shared<thread>(runfn, this);
	m_severManagerThread->join();
}

void TServerManager::run()
{
	while (m_closedServer)
	{
		lock_guard<mutex> lck(m_mutex);

		auto newClientSocketUnique = m_mainServerSocket->popSocket();
		auto newUser = TServerUser::makeShared();


		m_connectionPool.emplace_back(newUser);
	}
}

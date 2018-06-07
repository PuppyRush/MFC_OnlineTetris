/*
 * ServerManager.h
 *
 *  Created on: 2018. 2. 11.
 *      Author: cmk
 */

#pragma once


#include <thread>
#include <queue>

#include "DefineInfo.h"
#include "TServerSocket.h"
#include "TUserServer.h"

using namespace std;

class TServerManager
{

public:

	TServerManager(const shared_ptr<TServerSocket> &socket);
	virtual ~TServerManager();

	void run();
	void BeginServer();

private:

	shared_ptr<std::thread> m_severManagerThread;
	shared_ptr<TServerSocket> m_mainServerSocket;

private:

	std::deque<shared_ptr<TUserServer>> m_connectionPool;
};

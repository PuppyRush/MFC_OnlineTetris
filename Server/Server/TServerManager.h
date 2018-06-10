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
	void beginServer();
	void closeServer();


private:

	bool m_closeServerSocket;

	shared_ptr<std::thread> m_severManagerThread;
	shared_ptr<TServerSocket> m_mainServerSocket;

	std::deque<shared_ptr<TUserServer>> m_connectionPool;
};

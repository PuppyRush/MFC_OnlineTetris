/*
 * ServerManager.h
 *
 *  Created on: 2018. 2. 11.
 *      Author: cmk
 */

#pragma once


#include <thread>
#include <queue>
#include <atomic>
#include <mutex>

#include "DefineInfo.h"
#include "TServerSocket.h"
#include "TUserServer.h"
#include "TType.h"



class TServerManager
{
	using namespace std;
	using namespace tetris_type;

public:

	TServerManager(const shared_ptr<TServerSocket> &socket);
	virtual ~TServerManager();

	void run();
	void BeginServer();

private:

	shared_ptr<std::thread> m_severManagerThread;
	shared_ptr<TServerSocket> m_mainServerSocket;

	std::deque<shared_ptr<TUserServer>> m_connectionPool;
	
	std::mutex m_mutex;

	static tUnique getUnique() noexcept
	{
		static tUnique tetrisUnique(0);
		return tetrisUnique++;
	}
};

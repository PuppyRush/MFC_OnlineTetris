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

#include "../../Commons/DefineInfo.h"
#include "../../Commons/TType.h"
#include "TServerSocket.h"
#include "TUserServer.h"

using namespace std;

class TServerManager
{
public:
	TServerManager(shared_ptr<TServerSocket> &socket);
	virtual ~TServerManager();

	void run();
	void beginServer();

private:
	shared_ptr<std::thread> m_severManagerThread;
	shared_ptr<TServerSocket> m_mainServerSocket;

	std::deque<shared_ptr<TUserServer>> m_connectionPool;
	std::mutex m_mutex;

	static const t_unique getUnique() noexcept
	{
		static t_uniqueAtomic tetrisUnique(0);
		tetrisUnique.fetch_add(1);
		return tetrisUnique.load();
	}

	bool m_closedServer;
};

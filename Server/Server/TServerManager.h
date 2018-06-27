/*
 * ServerManager.h
 *
 *  Created on: 2018. 2. 11.
 *      Author: cmk
 */

#pragma once

#include <thread>
#include <deque>
#include <atomic>
#include <mutex>

#include "../../Commons/DefineInfo.h"
#include "../../Commons/TType.h"
#include "TServerSocket.h"

class TServerUser;
class TServerSocket;

using namespace std;

class TServerManager
{
public:
	TServerManager(std::shared_ptr<TServerSocket> &socket);
	virtual ~TServerManager();

	void run();
	void beginServer();

private:
	shared_ptr<thread> m_severManagerThread;
	shared_ptr<TServerSocket> m_mainServerSocket;

	deque<shared_ptr<TServerUser>> m_connectionPool;
	mutex m_mutex;

	static const tetris::t_unique getUnique() noexcept
	{
		static tetris::t_uniqueAtomic tetrisUnique(0);
		tetrisUnique.fetch_add(1);
		return tetrisUnique.load();
	}

	bool m_closedServer;
};

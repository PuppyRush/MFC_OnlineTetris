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
#include "../../Commons/TAtomic.h"
#include "TServerSocket.h"
#include "TServerUser.h"

class TServerManager 
{
public:
	
	virtual ~TServerManager();

	void run();
	void beginServer();

	inline static std::shared_ptr<TServerManager> get()
	{
		static std::shared_ptr<TServerManager> socket = std::shared_ptr<TServerManager>(new TServerManager());
		return socket;
	}

private:
	TServerManager();

    void makeWaitingRoom();
    void HelloUser(const tetris::t_socket);

	std::shared_ptr<std::thread> m_severManagerThread;
	std::shared_ptr<TServerSocket> m_mainServerSocket;

	std::mutex m_mutex;
	
	bool m_closedServer;
};

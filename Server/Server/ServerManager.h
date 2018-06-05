/*
 * ServerManager.h
 *
 *  Created on: 2018. 2. 11.
 *      Author: cmk
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <queue>

#include "DefineInfo.h"

namespace server_manager {

class ServerManager {

public:
	static void* run(void* param) {
		auto sm = static_cast<ServerManager*>(param);
		return sm->BeginServer();
	}

	ServerManager();
	virtual ~ServerManager();

private:

	typedef struct connectionThreadParam
	{
		struct sockaddr_in clientaddr;
		int clientSocket;
		connectionThreadParam(struct sockaddr_in _clientaddr, int _clientSocket)
		:clientaddr(_clientaddr), clientSocket(_clientSocket)
		{	}
	};



private:
	void* BeginServer();
	static void* AcceptAndWaitConnectionClient(void* sock);
	static unsigned long long GetUniqueOrder();

private:

	const size_t MAX_WAITING_COUNT;
	std::deque<pthread_t> waitingPool;
};

} /* namespace ctimer */

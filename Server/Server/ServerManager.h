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

	void* BeginServer();
	static void* AcceptAndWaitConnectionClient(void* sock);

private:

	const size_t MAX_WAITING_COUNT;

	std::deque<pthread_t> waitingPool;
};

} /* namespace ctimer */

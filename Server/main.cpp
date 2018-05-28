/*
 * main.cpp
 *
 *  Created on: 2018. 2. 6.
 *      Author: cmk
 */

#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "Server/ServerManager.h"

using namespace std;
using namespace server_manager;

int main()
{

	pthread_t server_main_thd_th=0;
	ServerManager sm;
	pthread_create(&server_main_thd_th, nullptr, &ServerManager::run,&sm);

	pthread_join(server_main_thd_th, nullptr);
}


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

#include "FileWatcher/FileWatcher.h"
#include "Server/ServerManager.h"

using namespace std;
using namespace file_watcher;
using namespace server_manager;

int main(){


	pthread_t server_main_thd_th=0;
	ServerManager sm;
	pthread_create(&server_main_thd_th, nullptr, &ServerManager::run,&sm);

	pthread_t file_watcher_thd_th=0;
	FileWatcher fw;
	pthread_create(&file_watcher_thd_th, nullptr, &FileWatcher::run,&fw);

	pthread_join(server_main_thd_th, nullptr);
}


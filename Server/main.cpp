/*
 * main.cpp
 *
 *  Created on: 2018. 2. 6.
 *      Author: cmk
 */

#include <iostream>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

#include "MessageHeader.h"

#include "Server/TServerManager.h"

using namespace std;

int main()
{
	auto serverSocket = make_shared<TServerSocket>();
	if(serverSocket->listen(5905u, 100))
	{
		if(serverSocket->accept()==0)
		{
			TServerManager servermanager(serverSocket);
			servermanager.BeginServer();
		}

	}

}


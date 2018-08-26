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

#include "Server/TServerManager.h"

int main()
{
	TServerManager::get()->beginServer();

	std::cout << "choice menu\n";
	while (1)
	{


	}
}


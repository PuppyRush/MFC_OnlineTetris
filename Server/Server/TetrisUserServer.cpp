/*
 * TetrisUserServer.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include "TetrisUserServer.h"

TetrisUserServer::TetrisUserServer(const string &name, const pthread_t tid, const ServerSocket socket)
:TetrisUser(name),tid(tid), socket(socket)
{
}

TetrisUserServer::~TetrisUserServer()
{
	// TODO Auto-generated destructor stub
}


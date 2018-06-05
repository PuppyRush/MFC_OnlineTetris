/*
 * TetrisUserServer.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <string>
#include <memory>
#include <TetrisUser.h>
#include "ServerSocket.h"

using namespace std;

class TetrisUserServer : public TetrisUser
{

protected:
	TetrisUserServer(const string &name, const pthread_t tid, const ServerSocket socket);


private:
	pthread_t tid;
	ServerSocket socket;

public:

	virtual ~TetrisUserServer();

	static shared_ptr<TetrisUserServer> MakeShared(const string &name,const pthread_t tid, const ServerSocket socket)
	{
		return shared_ptr<TetrisUserServer>(new TetrisUserServer(name, tid,socket));
	}


};


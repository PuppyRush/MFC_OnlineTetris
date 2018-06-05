/*
 * ServerSocket.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

class ServerSocket : public SocketImpl
{
private:
	int socket;

public:
	ServerSocket();
	virtual ~ServerSocket();
};


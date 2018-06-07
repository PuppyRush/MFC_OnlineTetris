/*
 * ServerSocket.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <sys/socket.h>

#include "TServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


TServerSocket::TServerSocket()
	:TSocketImpl(AF_INET,SOCK_STREAM,0)
{}

TServerSocket::~TServerSocket()
{
	// TODO Auto-generated destructor stub
}

TServerSocket::TServerSocket(const unsigned socket)
	:TSocketImpl(AF_INET,SOCK_STREAM,0)
{
	m_socket = socket;
	m_closeSocket = true;
}

unsigned TServerSocket::_close(const unsigned _socket)
{

}

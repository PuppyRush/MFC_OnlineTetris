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

using namespace tetris;

TServerSocket::TServerSocket()
	:TSocketImpl(AF_INET, SOCK_STREAM, 0, IPString{ 192,168,0,1 },5905)
{}

TServerSocket::~TServerSocket()
{
	// TODO Auto-generated destructor stub
}

TServerSocket::TServerSocket(const unsigned socket)
	:TSocketImpl(AF_INET, SOCK_STREAM, 0, IPString{ 192,168,0,1 }, 5905)
{
	m_socket = socket;
	m_closeSocket = true;
}

void TServerSocket::switchingMessage(const msgElement &msg)
{
	const auto header = Header::get(msgHelper::getMessage(msg));
	switch (header.msgIdx)
	{
		
	}
}

void TServerSocket::recvConnectionInfo(msgElement &msg)
{

}
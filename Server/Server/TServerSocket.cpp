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
	:TSocketImpl(AF_INET, SOCK_STREAM, 0, IPString{ 192,168,0,1 }, 5905)
{}

TServerSocket::TServerSocket(tetris::t_socket socket)
	: TSocketImpl(AF_INET, SOCK_STREAM, 0, IPString{ 192,168,0,1 }, 5905)
{
	setSocket(socket);
	m_closeSocket = true;
}


TServerSocket::~TServerSocket()
{
	// TODO Auto-generated destructor stub
}


//void TServerSocket::switchingMessage(const tetris::msgElement &msg)
//{
//	const auto header = Header::getHeader(msgHelper::getMessage(msg));
//	switch (header.msgIdx)
//	{
//	case toUType(SERVER_MSG::ON_CONNECTION_INFO):
//		recvConnectionInfo(msg);
//		sendConnectionInfo();
//		break;
//	default:
//		assert(false);
//		//logger
//	}
//}

void TServerSocket::recvConnectionInfo(const tetris::msgElement &msg)
{
	const auto message = toMessage<mOnName>(msg);
	//setName(string(message.name));

	//TWaitingRoom::getWaitingRoom()->add(m_sharedPtr);
}

void TServerSocket::sendConnectionInfo()
{
	const auto userinfo = TWaitingRoom::getWaitingRoom()->getUserInfo();
	const size_t size = userinfo.size();
	UserInfo* userinfoAry = new UserInfo[size];

	for (int i = 0; i < size; i++)
		userinfoAry[i] = UserInfo(userinfo.at(i).userUnique, userinfo.at(i).name);

	const auto header = Header(Priority::High, toUType(CLIENT_MSG::ON_CONNECTION_INFO));
	//mSendConnectionInfo msg(header, getUnique(), userinfoAry, size);
	//pushMessage(&msg);

	delete[] userinfoAry;
}

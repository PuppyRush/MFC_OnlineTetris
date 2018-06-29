<<<<<<< HEAD
/*
 * TetrisUserServer.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <string>
#include <sys/socket.h>

#include "../../Commons/MessageHeader.h"
#include "TServerUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TServerUser::TServerUser(tetris::t_socket socket, const tetris::t_unique unique)
	:TSocketImpl(AF_INET, SOCK_STREAM, 0, IPString{ 192,168,0,1 }, 5905)
{
	setUnique(unique);
}

TServerUser::~TServerUser()
{
	// TODO Auto-generated destructor stub
}

void TServerUser::switchingMessage(const tetris::msgElement &msg)
{
	const auto header = Header::getHeader(msgHelper::getMessage(msg));
	switch (header.msgIdx)
	{
	case toUType(SERVER_MSG::ON_CONNECTION_INFO):
		recvConnectionInfo(msg);
		break;
	}
}

void TServerUser::recvConnectionInfo(const tetris::msgElement &msg)
{
	const auto message = toMessage<mOnName>(msg);
	setName(string(message.name));
}

void TServerUser::sendConnectionInfo()
{
	const auto header = Header(toUType(CLIENT_MSG::ON_CONNECTION_INFO));
	//mSendConnectionInfo msg(header, getUnique());
	//pushMessage(&msg);
}
=======
/*
 * TetrisUserServer.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <string>
#include <sys/socket.h>

#include "../Room/TWaitingRoom.h"
#include "../../Commons/MessageHeader.h"
#include "TServerUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TServerUser::TServerUser(tetris::t_socket socket, const tetris::t_userUnique unique)
	:TServerSocket(),
	m_sharedPtr(make_shared<TServerUser>(this))
{
}

TServerUser::TServerUser(TServerUser* user)
	:TServerSocket()
{
}

TServerUser::~TServerUser()
{
	// TODO Auto-generated destructor stub
}

void TServerUser::switchingMessage(const tetris::msgElement &msg)
{
	const auto header = Header::getHeader(msgHelper::getMessage(msg));
	switch (header.msgIdx)
	{
	case toUType(SERVER_MSG::ON_CONNECTION_INFO):
		recvConnectionInfo(msg);
		sendConnectionInfo();
		break;
	}
}

void TServerUser::recvConnectionInfo(const tetris::msgElement &msg)
{
	const auto message = toMessage<mOnName>(msg);
	setName(string(message.name));

	TWaitingRoom::getWaitingRoom()->add(m_sharedPtr);
}

void TServerUser::sendConnectionInfo()
{
	const auto userinfo = TWaitingRoom::getWaitingRoom()->getUserInfo();
	const size_t size = userinfo.size();
	UserInfo* userinfoAry = new UserInfo[size];
	
	for (int i = 0; i < size ; i++)
		userinfoAry[i] = UserInfo(userinfo.at(i).userUnique, userinfo.at(i).name);

	const auto header = Header(Priority::High, toUType(CLIENT_MSG::ON_CONNECTION_INFO));
	mSendConnectionInfo msg(header, getUnique(), userinfoAry,size);
	pushMessage(&msg);

	delete[] userinfoAry;
}
>>>>>>> origin/splited-server

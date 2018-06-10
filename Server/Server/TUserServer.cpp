/*
 * TetrisUserServer.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <string>

#include "TUserServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

TUserServer::TUserServer(const std::shared_ptr<TServerSocket> &socket, const tetris_Type::tUnique unique);
	:m_socket(socket),
	m_unique(unique)
{
}

TUserServer::~TUserServer()
{
	// TODO Auto-generated destructor stub
}

void TUserServer::run()
{
	const auto popFn = &TUserServer::poppingMessage;
	m_popThread = make_shared<std::thread>(popFn,this);
}

void TUserServer::poppingMessage();
{
	while(m_closeSocket)
	{
		const auto msg = popMessage();
		switchingMessage(msg);
	}
}

void TUserServer::switchingMessage(const msg_element &msg)
{
	const header = Header::get(msgHelper::getMessage(msg));
	switch(header.msgidx)
	{
		
	}
}

void TUserServer::recvConnectionInfo(msg_element &msg)
{

}
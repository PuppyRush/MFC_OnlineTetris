#include "StdAfx.h"

#include <numeric>

#include "TClientUser.h"
#include "../Commons/DefineInfo.h"
#include "../Commons/TMessageSender.h"
#include "TClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#endif

TClientUser::TClientUser()
	:TetrisUser(numeric_limits<tetris::t_socket>::max())
{
	registryMessage();
}

void TClientUser::registryMessage()
{
	this->addCaller(make_pair(toUType(SERVER_MSG::CONNECTION_INFO), std::bind(&TClientUser::updateUserInfo, this, std::placeholders::_1)));
}

void TClientUser::updateUserInfo(const TMessageObject& msg)
{
	auto info = TMessageObject::toMessage<mConnectionInfo>(msg);
	updateUnique(SERVER_MSG::CONNECTION_INFO, info.userUnique);

	const auto header = Header(toUType(Priority::Normal), toUType(SERVER_MSG::CONNECTION_INFO));
	const mName sendname(header, getUnique(), getUserName().size(), getUserName().c_str());

	T_SEND(TClientSocket::get()->getSocket(), &sendname);
}
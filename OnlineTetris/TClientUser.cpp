#include "StdAfx.h"
#include "TClientUser.h"
#include "../Commons/DefineInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#endif

void TClientUser::registryMessage()
{
	this->addCaller(make_pair(toUType(SERVER_MSG::CONNECTION_INFO), std::bind(&TClientUser::updateUserInfo, this, std::placeholders::_1)));
}

void TClientUser::updateUserInfo(const TMessageObject& msg)
{
	auto info = TMessageObject::toMessage<mConnectionInfo>(msg);
	updateUnique(SERVER_MSG::CONNECTION_INFO, info.userUnique);
}
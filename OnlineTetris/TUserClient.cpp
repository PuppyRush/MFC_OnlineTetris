#include "StdAfx.h"
#include "TUserClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#endif
TUserClient::TUserClient(const string &name)
	:TetrisUser(name)
{
}

TUserClient::TUserClient(const string &name, const IPString &ip, CTClientSocket* soc, const int idx)
	:TetrisUser(name, ip, idx), Socket(soc)
{
	Socket = soc;
}


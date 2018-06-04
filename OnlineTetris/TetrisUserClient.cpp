#include "StdAfx.h"
#include "TetrisUserClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#endif
TetrisUserClient::TetrisUserClient(const string &name)
	:TetrisUser(name)
{
}

TetrisUserClient::TetrisUserClient(const string &name, const IPString &ip, CClientSocket* soc, const int idx)
	:TetrisUser(name, ip, idx), Socket(soc)
{
	Socket = soc;
}


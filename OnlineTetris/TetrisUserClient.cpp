#include "StdAfx.h"
#include "TetrisUserClient.h"

TetrisUserClient::TetrisUserClient(const string &name)
	:TetrisUser(name)
{
}

TetrisUserClient::TetrisUserClient(const string &name, const IPString &ip, CMySocket* soc, const int idx)
	:TetrisUser(name, ip, idx), Socket(soc)
{
	Socket = soc;
}


#pragma once

#include "../Commons/structs.h"
#include "../Commons/TetrisUser.h"

class CMySocket;

class TetrisUserClient : public TetrisUser
{
private:
	CMySocket *Socket;

public:
	
	explicit TetrisUserClient(const string &name);
	explicit TetrisUserClient(const string &name, const IPString &ip, CMySocket* soc, const int idx);
	virtual ~TetrisUserClient(void)	{}

	static shared_ptr<TetrisUserClient> MakeShared(const string &name)
	{
		return make_shared<TetrisUserClient>(name);
	}

	static shared_ptr<TetrisUserClient> MakeShared(const string &name, const IPString &ip, CMySocket* soc, const int idx)
	{
		return make_shared<TetrisUserClient>(name, ip, soc, idx);
	}

	inline CMySocket *GetSocket()
	{
		return Socket;
	}
};
using SHR_USRC = std::shared_ptr<TetrisUserClient>;
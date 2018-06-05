#pragma once

#include "../Commons/structs.h"
#include "../Commons/TetrisUser.h"

class CClientSocket;

class TetrisUserClient : public TetrisUser
{
private:
	CClientSocket *Socket;

public:
	
	TetrisUserClient()	{}
	explicit TetrisUserClient(const string &name);
	explicit TetrisUserClient(const string &name, const IPString &ip, CClientSocket* soc, const int idx);
	virtual ~TetrisUserClient(void)	{}

	static shared_ptr<TetrisUserClient> MakeShared(const string &name)
	{
		return make_shared<TetrisUserClient>(name);
	}

	static shared_ptr<TetrisUserClient> MakeShared(const string &name, const IPString &ip, CClientSocket* soc, const int idx)
	{
		return make_shared<TetrisUserClient>(name, ip, soc, idx);
	}

	inline CClientSocket *GetSocket()
	{
		return Socket;
	}

	static shared_ptr<TetrisUserClient> GetMe()
	{
		static const auto clientofmine = make_shared<TetrisUserClient>();
		return clientofmine;
	}

};
using SHR_USRC = std::shared_ptr<TetrisUserClient>;
#pragma once

#include "../Commons/structs.h"
#include "../Commons/TUser.h"

class CTClientSocket;

class TUserClient : public TetrisUser
{
private:
	CTClientSocket *Socket;

public:
	
	TUserClient()	{}
	explicit TUserClient(const string &name);
	explicit TUserClient(const string &name, const IPString &ip, CTClientSocket* soc, const int idx);
	virtual ~TUserClient(void)	{}

	static shared_ptr<TUserClient> MakeShared(const string &name)
	{
		return make_shared<TUserClient>(name);
	}

	static shared_ptr<TUserClient> MakeShared(const string &name, const IPString &ip, CTClientSocket* soc, const int idx)
	{
		return make_shared<TUserClient>(name, ip, soc, idx);
	}

	inline CTClientSocket *GetSocket()
	{
		return Socket;
	}

	static shared_ptr<TUserClient> GetMe()
	{
		static const auto clientofmine = make_shared<TUserClient>();
		return clientofmine;
	}

};
using SHR_USRC = std::shared_ptr<TUserClient>;
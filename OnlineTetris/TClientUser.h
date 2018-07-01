#pragma once

#include "../Commons/structs.h"
#include "../Commons/TUser.h"

class CTClientSocket;

class TClientUser : public TetrisUser
{
private:
	CTClientSocket *Socket;

public:

	TClientUser() {}
	virtual ~TClientUser(void)	{}

	inline CTClientSocket* GetSocket()
	{
		return Socket;
	}

	static shared_ptr<TClientUser> GetMe()
	{
		static const auto clientofmine = make_shared<TClientUser>();
		return clientofmine;
	}

};
using SHR_USRC = std::shared_ptr<TClientUser>;
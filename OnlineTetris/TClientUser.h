#pragma once

#include "../Commons/structs.h"
#include "../Commons/TUser.h"

class TClientSocket;

class TClientUser : public TetrisUser
{
private:
	TClientSocket *Socket;

public:

	TClientUser() {}
	virtual ~TClientUser(void)	{}

	inline TClientSocket* GetSocket()
	{
		return Socket;
	}

	static shared_ptr<TClientUser> get()
	{
		static const auto clientofmine = make_shared<TClientUser>();
		return clientofmine;
	}

};
using SHR_USRC = std::shared_ptr<TClientUser>;
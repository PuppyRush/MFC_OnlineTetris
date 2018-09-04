#pragma once

#include <memory>

#include "../Commons/structs.h"
#include "../Commons/Entity/TUser.h"

class TClientSocket;

class TClientUser : public TetrisUser
{
public:
	virtual ~TClientUser(void)	{}
	virtual void registryMessage();

	inline TClientSocket* GetSocket()
	{
		return Socket;
	}

	static std::shared_ptr<TClientUser> get()
	{
		static const auto clientofmine = std::shared_ptr<TClientUser>(new TClientUser());
		return clientofmine;
	}
private:
	TClientUser() {}
	TClientSocket * Socket;

};

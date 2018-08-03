#pragma once

#include <memory>

#include "../Commons/structs.h"
#include "../Commons/TUser.h"

class TClientSocket;

class TClientUser : public TetrisUser
{
public:
	virtual ~TClientUser(void)	{}
	virtual const tetris::t_error switchingMessage(const tetris::msgElement &msg);

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

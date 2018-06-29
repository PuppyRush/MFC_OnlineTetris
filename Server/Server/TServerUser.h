<<<<<<< HEAD
/*
 * TetrisUserServer.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <atomic>

#include "../../Commons/TUser.h"
#include "../../Commons/TType.h"
#include "TServerSocket.h"

using namespace std;

class TServerUser : public TetrisUser, public TSocketImpl
{
public:
	TServerUser(tetris::t_socket socekt, const tetris::t_unique unique);
	virtual ~TServerUser() override;

	static shared_ptr<TServerUser> makeShared(const tetris::t_socket newsocket, const tetris::t_unique unique)
	{
		return make_shared<TServerUser>(newsocket, unique);
	}

protected:
	
	virtual void switchingMessage(const tetris::msgElement &msg);

private:

	void recvConnectionInfo(const tetris::msgElement &msg);
	void sendConnectionInfo();
};
=======
/*
 * TetrisUserServer.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <atomic>

#include "../../Commons/TUser.h"
#include "../../Commons/TType.h"
#include "TServerSocket.h"

using namespace std;

class TServerUser : public TetrisUser, public TServerSocket
{
public:
	TServerUser() {}
	TServerUser(TServerUser* user);
	TServerUser(tetris::t_socket socekt, const tetris::t_userUnique unique);
	virtual ~TServerUser() override;

	static shared_ptr<TServerUser> makeShared(const tetris::t_socket newsocket, const tetris::t_userUnique unique)
	{
		return make_shared<TServerUser>(newsocket, unique);
	}

protected:
	
	virtual void switchingMessage(const tetris::msgElement &msg);
	

private:
	shared_ptr<TServerUser> m_sharedPtr;

	void recvConnectionInfo(const tetris::msgElement &msg);
	void sendConnectionInfo();
};
>>>>>>> origin/splited-server

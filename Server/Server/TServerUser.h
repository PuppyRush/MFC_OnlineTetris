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

class TServerUser : public TetrisUser
{
public:

	virtual const tetris::t_error switchingMessage(const tetris::msgElement &msg) override;
	virtual ~TServerUser() override;

	static shared_ptr<TServerUser> makeShared()
	{
		const auto unique = TetrisUser::newUnique();
		return shared_ptr<TServerUser>(new TServerUser(unique));
	}

private:
	TServerUser() {}
	TServerUser(TServerUser* user);
	TServerUser(const tetris::t_userUnique unique);

	shared_ptr<TServerUser> m_sharedPtr;
};
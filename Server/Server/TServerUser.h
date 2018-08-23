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

class TServerUser : public TetrisUser
{
public:
	virtual ~TServerUser();
	virtual const tetris::t_error registryMessage() override;

	static std::shared_ptr<TServerUser> makeShared(const std::shared_ptr<TServerSocket> socket)
	{
		const auto unique = TetrisUser::newUnique();
		return std::shared_ptr<TServerUser>(new TServerUser(unique, socket));
	}

	inline std::shared_ptr<TServerSocket> getServerSocket() const noexcept
	{ return m_serverSocket; }

protected:
	TServerUser(TServerUser* user);
	TServerUser(const tetris::t_userUnique unique, const std::shared_ptr<TServerSocket> socket);

private:
	TServerUser() = delete;

	std::shared_ptr<TServerSocket> m_serverSocket;
	std::shared_ptr<TServerUser> m_sharedPtr;
};

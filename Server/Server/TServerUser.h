/*
 * TetrisUserServer.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <atomic>

#include "../../Commons/Entity/TUser.h"
#include "../../Commons/TType.h"
#include "TServerSocket.h"
#include "TMessageObject.h"


class TServerUser : public TetrisUser
{
public:
	virtual ~TServerUser();
	virtual void registryMessage() override;

	static std::shared_ptr<TServerUser> makeShared(const std::shared_ptr<TServerSocket> socket)
	{
		return std::shared_ptr<TServerUser>(new TServerUser(socket));
	}

	inline std::shared_ptr<TServerSocket> getServerSocket() const noexcept
	{ return m_serverSocket; }

protected:
	TServerUser(TServerUser* user);
	TServerUser(const std::shared_ptr<TServerSocket> socket);

private:
	TServerUser() = delete;
	void recvConnectionInfo(const TMessageObject& msg);

	std::shared_ptr<TServerSocket> m_serverSocket;
	std::shared_ptr<TServerUser> m_sharedPtr;
};

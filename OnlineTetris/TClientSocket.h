#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <memory>

#include "../Commons/MessageHeader.h"
#include "../Commons/structs.h"
#include "../Commons/TType.h"

#include "SocketImpl.h"
#include "TUserClient.h"

using namespace tetris;

class CTClientSocket : public SocketImpl
{
public:

	CTClientSocket();
	explicit CTClientSocket(const int domain, const int type, const int protocol, const IPString ip, const t_port port);
	virtual ~CTClientSocket();

	virtual void switchingMessage(const msgElement &msg);

	void SelfClose();
	void Broadcast(void* strc, int msgidx);
	void Sendname(const char* name, int namelen);
	void Sendmapstate();
	void Sendready(bool isReady);
	void SendDead();
	void SendRestart();
	void SendLine(int , bool);
	void ProcessReady(mOnReady rdy);
	void ProcessMapsate(mOnMapstate on_map);

	inline bool isConnected() { return m_isConnected; }

	inline static shared_ptr<CTClientSocket> GetSocket()
	{
		static shared_ptr<CTClientSocket> clientSocket = make_shared<CTClientSocket>();
		return clientSocket;
	}

private:
	shared_ptr<TUserClient> m_me;
	bool m_isConnected;
};



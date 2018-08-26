#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <memory>

#include "../Commons/MessageHeader.h"
#include "../Commons/structs.h"
#include "../Commons/TType.h"

#include "SocketImpl.h"
#include "TClientUser.h"

class TClientSocket : public SocketImpl
{
public:
	//explicit TClientSocket(const int domain, const int type, const int protocol, const IPString ip, const t_port port);
	virtual ~TClientSocket();
	virtual void registryMessage();

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

	inline static shared_ptr<TClientSocket> get()
	{
		static shared_ptr<TClientSocket> clientSocket = shared_ptr<TClientSocket>(new TClientSocket());
		return clientSocket;
	}

private:
	TClientSocket();

	shared_ptr<TClientUser> m_me;
	bool m_isConnected;
};



#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <memory>

#include "../Commons/MessageHeader.h"
#include "SocketImpl.h"
#include "TUserClient.h"

class CTClientSocket : public SocketImpl
{

public:

	CTClientSocket();
	CTClientSocket(const int domain, const int type, const int protohcol);
	virtual ~CTClientSocket();

	template<class... _Types>
	static shared_ptr<CTClientSocket> GetSocket(_Types&&... _Args)
	{
		static shared_ptr<CTClientSocket> mysocket = make_shared<CTClientSocket>(forward<_Types>(_Args)...);
		return mysocket;
	}

	bool Connect(const IPString, const unsigned port);
	void recvMsg();
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

private:

	TUserClient m_me;
	std::thread m_msgThread;
	std::mutex m_recvMsgMutex;
	bool m_isConnected;

private:

	void createThread();

};



#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <memory>

#include "../Commons/MessageHeader.h"
#include "SocketImpl.h"

class CClientSocket : public SocketImpl
{

public:

	CClientSocket();
	CClientSocket(const int domain, const int type, const int protohcol);
	virtual ~CClientSocket();

	template<class... _Types>
	static shared_ptr<CClientSocket> GetSocket(_Types&&... _Args)
	{
		static shared_ptr<CClientSocket> mysocket = make_shared<CClientSocket>(forward<_Types>(_Args)...);
		return mysocket;
	}

	void Connect(const IPString, const unsigned port);
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

	TetrisUserClient m_me;
	std::thread m_msgThread;
	std::mutex m_recvMsgMutex;
	bool m_isConnected;

private:

	void createThread();

};



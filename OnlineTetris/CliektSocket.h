#pragma once

// CMySocket 명령 대상입니다.

#include "../Commons/MessageHeader.h"
#include "../Commons/structs.h"

class CMyView;
class CMyDoc;

class CClientSocket : public CSocket
{
private:
	CClientSocket()
		:m_ipString({192,168,0,1})
	{}

public:

	CClientSocket(const IPString ipstring, const size_t port);

	IPString m_ipString;
	size_t m_port;
	string m_username;

	CMyView *pView;
	CMyDoc *pDoc;

	template<class... _Types>
	static shared_ptr<CClientSocket> GetSocket(_Types&&... _Args)
	{
		static auto mysocket = make_shared<CClientSocket>(forward<_Types>(_Args)...);
		return mysocket;
	}


public:
	
	virtual ~CClientSocket();
	bool ConnectToServer();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	void SelfClose();
	bool Broadcast(void* strc, int msgidx);
	bool SendConnectionInfo();
	bool Sendname(const char* name, int namelen);
	bool Sendmapstate();
	bool Sendready(bool isReady);
	bool SendDead();
	bool SendRestart();
	bool SendLine(int , bool);
	bool ProcessReady(mOnReady rdy);
	bool ProcessMapsate(mOnMapstate on_map);
};



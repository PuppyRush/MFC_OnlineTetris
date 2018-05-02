#pragma once

// CMySocket 명령 대상입니다.

#include "../Commons/MessageHeader.h"
#include "../Commons/structs.h"

class CMyView;
class CMyDoc;

class CMySocket : public CSocket
{
public:

	using SHR_SVRSOC = shared_ptr<CServerSocket>;

public:

	CMySocket(const IPString ipstring, const size_t port);

	IPString m_ipString;
	size_t m_port;
	string m_username;

	CMyView *pView;
	CMyDoc *pDoc;

	template<class... _Types>
	static shared_ptr<CMySocket> GetSocket(_Types&&... _Args)
	{
		static auto mysocket = make_shared<CMySocket>(forward<_Types>(_Args)...);
		return mysocket;
	}


public:
	
	virtual ~CMySocket();
	bool ConnectToServer();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	void SelfClose();
	bool Broadcast(void* strc, int msgidx);
	bool Sendname(const char* name, int namelen);
	bool Sendmapstate();
	bool Sendready(bool isReady);
	bool SendDead();
	bool SendRestart();
	bool SendLine(int , bool);
	bool ProcessReady(mOnReady rdy);
	bool ProcessMapsate(mOnMapstate on_map);
};



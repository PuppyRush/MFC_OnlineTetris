#pragma once

// CMySocket 명령 대상입니다.

#include "../Commons/MessageHeader.h"
#include "../Commons/structs.h"

class CMyView;
class CMyDoc;

class CClientSocket : public CSocket
{

public:

	CClientSocket(const IPString ipstring, const size_t port);
	CClientSocket();

	template<class... _Types>
	static shared_ptr<CClientSocket> GetSocket(_Types&&... _Args)
	{
		static shared_ptr<CClientSocket> mysocket = make_shared<CClientSocket>(forward<_Types>(_Args)...);
		static bool isCreated = false;
		
		if(!isCreated)
			if(mysocket->Create())
				isCreated = true;
		return mysocket;
	}

public:
	
	virtual ~CClientSocket();

	void SetIP(const IPString &ip)
	{
		m_ipString = ip;
	}

	void SetPort(const size_t port)
	{
		m_port = port;
	}

	bool ConnectToServer();
	virtual void OnConnect(int nErrorCode);
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

	bool isConnected() { return m_isConnected; }

private:
	IPString m_ipString;
	size_t m_port;
	string m_username;
	bool m_isConnected;

	CMyView *pView;
	CMyDoc *pDoc;
};



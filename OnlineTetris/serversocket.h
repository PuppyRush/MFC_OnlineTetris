#pragma once

// CServerSocket 명령 대상입니다.

#include <afxsock.h>

#include <iostream>
#include <string>
#include <memory>

using namespace std;

class CServerSocket : public CSocket
{



public:

	

private:
	CServerSocket();

public:
	
	virtual ~CServerSocket();

	virtual void OnAccept(int);
	virtual void OnClose(int);

	//static shared_ptr<CServerSocket> MakeShared(const string &username, const IPString ipstring, const int port)
	//{
	//	return make_shared<CServerSocket>(username, ipstring, port);
	//}

	

	
};



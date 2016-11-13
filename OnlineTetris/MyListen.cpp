// MyListen.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "MyListen.h"
#include "MyDoc.h"
#include "MySocket.h"

// CMyListen

CMyListen::CMyListen()
{
}


CMyListen::~CMyListen()
{
}


void CMyListen::OnAccept(int nErrorCode){
	
	
 	if(pDoc->Server_UserList.GetCount() > MAX_ENTER){
		return;
	}
	else if(pDoc->Start)
		return;

	else{
		CMySocket *soc = new CMySocket();
		soc->pView = pView;
		soc->pDoc = pDoc;
		if(Accept(*soc)){

			CString ip;
			UINT port;
			soc->GetPeerName(ip, port);
			TUser *temp = new TUser( _T(""), ip, soc, -1);
		
			pDoc->Server_UserList.AddTail( temp);
			pDoc->SocketList.AddTail(soc);
	
		}
		else
			pView->MessageHandler(FAIL_ACCEPT);
	}
}

// CMyListen 멤버 함수


void CMyListen::OnClose(int nErrorCode){

	return ;
}
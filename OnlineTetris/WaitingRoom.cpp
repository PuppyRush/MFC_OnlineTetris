// WaitingRoom.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "WaitingRoom.h"
#include "afxdialogex.h"

// WaitingRoom 대화 상자입니다.

IMPLEMENT_DYNAMIC(WaitingRoom, CDialog)

WaitingRoom::WaitingRoom(CWnd* pParent /*=NULL*/)
	: CDialog(_DLG_WAITINGROOM, pParent)
{

}

WaitingRoom::~WaitingRoom()
{
}

void WaitingRoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WaitingRoom, CDialog)
END_MESSAGE_MAP()


// WaitingRoom 메시지 처리기입니다.

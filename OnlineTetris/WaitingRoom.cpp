// WaitingRoom.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "WaitingRoom.h"
#include "afxdialogex.h"

// WaitingRoom ��ȭ �����Դϴ�.

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


// WaitingRoom �޽��� ó�����Դϴ�.

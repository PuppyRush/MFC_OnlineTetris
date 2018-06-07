// WaitingRoom.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "WaitingRoom.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#endif
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
	DDX_Control(pDX, _LST_WAITING, roomList);
}


BEGIN_MESSAGE_MAP(WaitingRoom, CDialog)
END_MESSAGE_MAP()


// WaitingRoom �޽��� ó�����Դϴ�.

BOOL WaitingRoom::OnInitDialog()
{
	roomList.InsertColumn(0, _T("�� ��ȣ"), NULL, 50);
	roomList.InsertColumn(1, _T("�̸�"), NULL, 150);
	roomList.InsertColumn(2, _T("�����ο�"), NULL, 50);
	roomList.InsertColumn(3, _T("�� �����ð�"), NULL, 50);

	return true;
}
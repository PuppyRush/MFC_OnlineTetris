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

IMPLEMENT_DYNAMIC(WaitingRoom, CDialogEx)

WaitingRoom::WaitingRoom(CWnd* pParent /*=NULL*/)
	: CDialogEx(_DLG_WAITINGROOM, pParent)
{

}

WaitingRoom::~WaitingRoom()
{
}

void WaitingRoom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, _LST_WAITING, m_roomList);
}


BEGIN_MESSAGE_MAP(WaitingRoom, CDialogEx)
END_MESSAGE_MAP()


// WaitingRoom �޽��� ó�����Դϴ�.

BOOL WaitingRoom::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_roomList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES);
	m_roomList.DeleteAllItems();

	m_roomList.InsertColumn(0, _T("�� ��ȣ"), NULL, 50);
	m_roomList.InsertColumn(1, _T("�̸�"), NULL, 150);
	m_roomList.InsertColumn(2, _T("�����ο�"), NULL, 50);
	m_roomList.InsertColumn(3, _T("�� �����ð�"), NULL, 50);

	return true;
}
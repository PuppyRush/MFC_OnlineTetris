// WaitingRoomDlg.cpp : ���� �����Դϴ�.
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
// WaitingRoomDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(WaitingRoomDlg, CDialogEx)

WaitingRoomDlg::WaitingRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(_DLG_WAITINGROOM, pParent)
{

}

WaitingRoomDlg::~WaitingRoomDlg()
{
}

void WaitingRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, _LST_WAITING, m_roomList);
}


BEGIN_MESSAGE_MAP(WaitingRoomDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &WaitingRoomDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// WaitingRoomDlg �޽��� ó�����Դϴ�.

BOOL WaitingRoomDlg::OnInitDialog()
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


void WaitingRoomDlg::getWaitingUsers(const shared_ptr<WaitingRoom> waitRoom)
{


}

void WaitingRoomDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}

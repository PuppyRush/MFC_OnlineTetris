// WaitingRoomDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "afxdialogex.h"

#include "OnlineTetris.h"
#include "WaitingRoomDialog.h"
#include "../Commons/TProperty.h"
#include "../Commons/TMessageObject.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#endif
// WaitingRoomDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(WaitingRoomDlg, CDialogEx)

WaitingRoomDlg::WaitingRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(_DLG_WAITINGROOM, pParent),
	m_waitingRoom(TWaitingRoom::get())
{
}

WaitingRoomDlg::~WaitingRoomDlg()
{
}

void WaitingRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, _LST_WAITING, m_roomList);
	DDX_Control(pDX, _LST_WIATGAMER, m_waitUserListBox);
}


BEGIN_MESSAGE_MAP(WaitingRoomDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &WaitingRoomDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// WaitingRoomDlg 메시지 처리기입니다.



BOOL WaitingRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_roomList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES);
	m_roomList.DeleteAllItems();

	m_roomList.InsertColumn(0, _T("방 번호"), NULL, 50);
	m_roomList.InsertColumn(1, _T("방 이름"), NULL, 150);
	m_roomList.InsertColumn(2, _T("참가인원(%d/%d)"), NULL, 50);
	m_roomList.InsertColumn(3, _T("방 생성시간"), NULL, 50);

	return true;
}

void WaitingRoomDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}

void WaitingRoomDlg::updateRoomInfo(const mWaitingUserInfo* info)
{
	for (size_t i = 0; i < info->userInfoSize; i++)
	{
		m_waitUserListBox.AddString(CString(info->userinfo[i].name.c_str()));
		
	}
}
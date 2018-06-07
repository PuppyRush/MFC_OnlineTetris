// WaitingRoom.cpp : 구현 파일입니다.
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
// WaitingRoom 대화 상자입니다.

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


// WaitingRoom 메시지 처리기입니다.

BOOL WaitingRoom::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_roomList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES);
	m_roomList.DeleteAllItems();

	m_roomList.InsertColumn(0, _T("방 번호"), NULL, 50);
	m_roomList.InsertColumn(1, _T("이름"), NULL, 150);
	m_roomList.InsertColumn(2, _T("참가인원"), NULL, 50);
	m_roomList.InsertColumn(3, _T("방 생성시간"), NULL, 50);

	return true;
}
// WaitingRoomDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "afxdialogex.h"

#include <algorithm>

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
	m_gamerooms.reserve(100);
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

	m_columnNames.emplace_back("방 번호");
	m_columnNames.emplace_back("방 이름");
	m_columnNames.emplace_back("참가인원(%d/%d)");
	m_columnNames.emplace_back("방 생성시간");

	for(int i=0; i < m_columnNames.size() ; i++)
	{
		m_roomList.InsertColumn(i, CString(m_columnNames.at(i).c_str()), NULL, 50);
	}
	
	return true;
}

void WaitingRoomDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}

void WaitingRoomDlg::updateRoomInfo(const mWaitingRoomInfo& info)
{
	for (size_t i = 0; i < info.waitingRoomSize; i++)
	{
		const auto &room = info.waitingRoom[i];
		auto it = std::find_if(m_gamerooms.begin(), m_gamerooms.end(), [&](const std::shared_ptr<RoomInfo> exroom)
		{
			return exroom->unique == room.unique;
		});

		if (it == m_gamerooms.end())
		{
			m_gamerooms.emplace_back(make_shared<RoomInfo>(room));
		}
	}
}

void WaitingRoomDlg::updateRoomUserInfo(const mWaitingUserInfo& info)
{
	for (size_t i = 0; i < info.userInfoSize; i++)
	{
		const auto &user = info.userinfo[i];
		auto it = std::find_if(m_users.begin(), m_users.end(), [&](const std::shared_ptr<UserInfo> exuser)
		{
			return exuser->userUnique == user.userUnique;
		});

		if (it == m_users.end())
		{
			m_users.emplace_back(make_shared<UserInfo>(user));
			m_waitUserListBox.AddString(CString(info.userinfo[i].name));
		}
	}
}
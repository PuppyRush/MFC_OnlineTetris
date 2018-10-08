// WaitingRoomDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "afxdialogex.h"

#include <algorithm>
#include <numeric>

#include "StringManager.h"
#include "OnlineTetris.h"
#include "WaitingRoomDialog.h"
#include "OptionDialog.h"
#include "TClientSocket.h"

#include "../Commons/TMessageSender.h"
#include "../Commons/TProperty.h"
#include "../Commons/TMessageObject.h"
#include "../Commons/Entity/Room/TIGameRoom.h"

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
	DDX_Control(pDX, _LIST_CHAT, m_chat);
}


BEGIN_MESSAGE_MAP(WaitingRoomDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &WaitingRoomDlg::OnBnClickedOk)
	ON_BN_CLICKED(_BTN_CREATEROOM, &WaitingRoomDlg::OnBnClickedBtnCreateroom)
END_MESSAGE_MAP()


BOOL WaitingRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_roomList.SetExtendedStyle(LVS_EX_FULLROWSELECT  | LVS_EX_GRIDLINES | LVS_EX_SINGLEROW);
	m_roomList.DeleteAllItems();
	m_columnNames.emplace_back("방 번호");
	m_columnNames.emplace_back("방 이름");
	m_columnNames.emplace_back("참가인원");
	m_columnNames.emplace_back("방 생성시간");

	for(int i=0; i < m_columnNames.size() ; i++)
	{
		m_roomList.InsertColumn(i, CString(m_columnNames.at(i).c_str()), NULL, 100);
	}
	
	//m_chat.setChatType(TChat::property_chat::


	return true;
}

void WaitingRoomDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}

void WaitingRoomDlg::updateGameRooms(const mWaitingGameRoomInfo& info)
{
	auto lastrow = m_roomList.GetItemCount();
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

			int col = 1;
			m_roomList.InsertItem(lastrow, StringManager::ToCStringFrom(room.roomNumber));
			m_roomList.SetItem(lastrow, col++, LVIF_TEXT, StringManager::ToCStringFrom(room.roomName),0, 0, 0, NULL);

			char buf[10];
			sprintf(buf, "%d/%d", room.currentUserCount, room.fullUserCount);
			m_roomList.SetItem(lastrow, col++, LVIF_TEXT, CString(buf), 0, 0, 0, NULL);

			//생성시간
			auto now = localtime(reinterpret_cast<const time_t*>(&room.makeTime));
			char time[100];
			sprintf(time, "%d일 %d시 %d분", now->tm_mday, now->tm_hour, now->tm_min);
			m_roomList.SetItem(lastrow, col++, LVIF_TEXT, CString(time), 0, 0, 0, NULL);

			//delete now;
			lastrow++;
		}
	}
}

void WaitingRoomDlg::updateWaitingRoom(const mWaitingRoomInfo& info)
{


}

void WaitingRoomDlg::updateRoomUser(const mWaitingUserInfo& info)
{
	for (size_t i = 0; i < info.userInfoSize; i++)
	{
		const auto &user = info.userinfo[i];
		auto it = std::find_if(m_users.begin(), m_users.end(), [&](const std::shared_ptr<UserInfo> exuser)
		{
			return exuser->unique == user.unique;
		});

		if (it == m_users.end())
		{
			m_users.emplace_back(make_shared<UserInfo>(user));
			m_waitUserListBox.AddString(CString(info.userinfo[i].name));
		}
	}
}



void WaitingRoomDlg::OnBnClickedBtnCreateroom()
{
	// TODO: Add your control notification handler code here

	auto dlg = CreateRoomDialog::getDialog();
	if (dlg->DoModal() == IDOK)
	{
		const auto header = Header(toUType(Priority::Normal), toUType(GAMEROOM_MSG::CREAT_INIT));
		RoomInfo roominfo(std::numeric_limits<tetris::t_unique>::max(),
			std::numeric_limits<tetris::t_time>::max(),
			dlg->m_roomname.c_str(),
			std::numeric_limits<tetris::t_unique>::max(),
			toUType(TIGameRoom::property::MaxCount),
			1);

		const mRoomInitInfo roominitinfo(
			header,
			TClientUser::get()->getUnique(),
			roominfo,
			toUType(dlg->m_map),
			toUType(dlg->m_level),
			dlg->m_ghost, dlg->m_gravity);

		T_SEND(TClientSocket::get()->getSocket(), &roominitinfo);

		//pDoc->Server_ProceeStart();
		//Btn_Ready->EnableWindow(false);
		//Btn_Start->EnableWindow(false);
	}
}

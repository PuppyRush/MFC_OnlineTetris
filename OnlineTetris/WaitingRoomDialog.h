#pragma once

#include <functional>
#include <string>

#include "afxcmn.h"
#include "TWaitingRoom.h"
#include "MyEdit.h"
#include "../Commons/TMessageObject.h"
#include "../Commons/structs.h"

// WaitingRoomDlg 대화 상자입니다.


class WaitingRoomDlg : public CDialogEx
{
DECLARE_DYNAMIC(WaitingRoomDlg)

public:
	WaitingRoomDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~WaitingRoomDlg();
	virtual BOOL OnInitDialog();
	
	static shared_ptr<WaitingRoomDlg> getDialog()
	{
		static auto dlg = std::make_shared<WaitingRoomDlg>();
		return dlg;
	}

	afx_msg void OnBnClickedOk();

	void updateRoomUserInfo(const mWaitingUserInfo& info);
	void updateRoomInfo(const mWaitingRoomsInfo& info);
protected:
	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = _DLG_WAITINGROOM
	};
#endif

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

private:

	enum class sortType
	{
		number,
		name,
		maketime,
		count
	};


	std::shared_ptr<TWaitingRoom> m_waitingRoom;
	CListCtrl m_roomList;
	CListBox m_waitUserListBox;

	std::function<bool(const std::shared_ptr<RoomInfo>, const std::shared_ptr<RoomInfo>)> m_sortfn;

	std::vector<string> m_columnNames;
	std::vector<std::shared_ptr<RoomInfo>> m_gamerooms;
	std::vector<std::shared_ptr<UserInfo>> m_users;

	
public:
	afx_msg void OnBnClickedBtnCreateroom();
	CChatEdit m_chat;
};

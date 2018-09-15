#pragma once
#include "afxcmn.h"
#include "TWaitingRoom.h"
#include "../Commons/TMessageObject.h"
#include "../Commons/structs.h"

// WaitingRoomDlg ��ȭ �����Դϴ�.


class WaitingRoomDlg : public CDialogEx
{
DECLARE_DYNAMIC(WaitingRoomDlg)

public:
	WaitingRoomDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~WaitingRoomDlg();
	virtual BOOL OnInitDialog();
	
	static shared_ptr<WaitingRoomDlg> getDialog()
	{
		static auto dlg = std::make_shared<WaitingRoomDlg>();
		return dlg;
	}

	CListCtrl m_roomList;
	CListBox m_waitUserListBox;

	afx_msg void OnBnClickedOk();

	void updateRoomInfo(const mWaitingUserInfo* info);

protected:
	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = _DLG_WAITINGROOM
	};
#endif

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	

	DECLARE_MESSAGE_MAP()

private:
	std::shared_ptr<TWaitingRoom> m_waitingRoom;
	
};

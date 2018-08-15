#pragma once
#include "afxcmn.h"


// WaitingRoomDlg 대화 상자입니다.


class WaitingRoom;

class WaitingRoomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WaitingRoomDlg)

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

public:
	WaitingRoomDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~WaitingRoomDlg();
	virtual BOOL OnInitDialog();

	static shared_ptr<WaitingRoomDlg> GetDialog()
	{
		static auto dlg = std::make_shared<WaitingRoomDlg>();
		return dlg;
	}

	void getWaitingUsers(const shared_ptr<WaitingRoom> waitRoom);

	CListCtrl m_roomList;
	afx_msg void OnBnClickedOk();
};

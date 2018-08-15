#pragma once
#include "afxcmn.h"


// WaitingRoomDlg ��ȭ �����Դϴ�.


class WaitingRoom;

class WaitingRoomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WaitingRoomDlg)

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

public:
	WaitingRoomDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
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

#pragma once


// WaitingRoom ��ȭ �����Դϴ�.

class WaitingRoom : public CDialog
{
	DECLARE_DYNAMIC(WaitingRoom)

protected:
	
	WaitingRoom(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	

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

	virtual ~WaitingRoom();

	static shared_ptr<WaitingRoom> GetDialog()
	{
		static auto dlg = shared_ptr<WaitingRoom>(new WaitingRoom());
		return dlg;
	}

};

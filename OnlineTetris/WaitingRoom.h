#pragma once


// WaitingRoom 대화 상자입니다.

class WaitingRoom : public CDialog
{
	DECLARE_DYNAMIC(WaitingRoom)

protected:
	
	WaitingRoom(CWnd* pParent = NULL);   // 표준 생성자입니다.
	

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

	virtual ~WaitingRoom();

	static shared_ptr<WaitingRoom> GetDialog()
	{
		static auto dlg = shared_ptr<WaitingRoom>(new WaitingRoom());
		return dlg;
	}

};

#pragma once

#include "afxdialogex.h"
#include "OnlineTetris.h"

// ConnectionDialog dialog

class ConnectingDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ConnectingDialog)

#define CONNECTING_TIMER 0
	
public:
	ConnectingDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ConnectingDialog();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	void run();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONNECTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_connecting;
	
private:
	const string m_baseString;
	string m_connectingString;
};

// ConnectionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ConnectingDialog.h"

// ConnectionDialog dialog

IMPLEMENT_DYNAMIC(ConnectingDialog, CDialogEx)

ConnectingDialog::ConnectingDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONNECTING, pParent)
	,m_baseString("conneting")
{
	m_connectingString.reserve(15);
}

ConnectingDialog::~ConnectingDialog()
{
}

void ConnectingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONNECT, m_connecting);
}


BEGIN_MESSAGE_MAP(ConnectingDialog, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// ConnectionDialog message handlers

void ConnectingDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	switch (nIDEvent)
	{
	case CONNECTING_TIMER:
		if (m_connectingString.size() == 10)
			m_connectingString = ".";
		else
			m_connectingString.append(".");
	
		CString str(m_baseString.c_str());
		str.Append((LPCTSTR)m_connectingString.c_str());
		m_connecting.SetWindowTextW(str);

		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void ConnectingDialog::run()
{
	
}

BOOL ConnectingDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetTimer(CONNECTING_TIMER, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

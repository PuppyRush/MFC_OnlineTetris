#pragma once
#include "afxwin.h"

#include "ServerSocket.h"

// ServerDialog ��ȭ �����Դϴ�.


class CMyListen;
class CMyDoc;
class CMyView;

class ServerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ServerDialog)

public:
	ServerDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ServerDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = _DLG_SERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CButton Edt_Create;
	CEdit Edt_Entername;
	CIPAddressCtrl Edt_Serverip;
	CEdit Edt_Servername;
	CEdit Edt_Serverport;
	CEdit Edt_Roomname;
	CEdit Edt_Portnum;

	CMyView *pView;
	CMyDoc *pDoc;
	
	CMyDoc::SEND_NAME send_name;
	CMyDoc::SEND_PERMIT per;
	
	afx_msg void OnBnClickedBtnCreate();
	afx_msg void OnBnClickedBtnEnter();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	
	
};

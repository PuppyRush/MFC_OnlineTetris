#pragma once


// ServerDialog 대화 상자입니다.


class CMyListen;
class CMyDoc;
class CMyView;

class ServerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ServerDialog)

public:
	ServerDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ServerDialog();

// 대화 상자 데이터입니다.
	enum { IDD = _SERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton Edt_Create;
	CEdit Edt_Entername;
	CIPAddressCtrl Edt_Serverip;
	CEdit Edt_Servername;
	CEdit Edt_Serverport;

	CMyView *pView;
	CMyDoc *pDoc;
	
	CMyDoc::SEND_NAME send_name;
	CMyDoc::SEND_PERMIT per;
	
	afx_msg void OnBnClickedEdtCreate();
	afx_msg void OnBnClickedButton3();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
};

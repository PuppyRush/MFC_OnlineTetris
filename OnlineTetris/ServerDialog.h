#pragma once


#include "afxdialogex.h"
#include "OnlineTetris.h"
#include "../Commons/structs.h"

#include <regex>

class CMyDoc;
class CMyView;

class ServerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ServerDialog)

public:
	ServerDialog(CWnd* pParent = NULL);   
	virtual ~ServerDialog();

	enum { IDD = _DLG_SERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()
public:
	CButton Edt_Create;
	CEdit Edt_Entername;
	CIPAddressCtrl Edt_Serverip;
	CEdit Edt_Servername;
	CEdit Edt_Serverport;
	CEdit Edt_Roomname;
	CEdit Edt_Portnum;

	string username;
	string roomname;
	IPString ipstring;
	size_t portnum;

	bool isValidationMakeRoomInfo;
	bool isValidationEnterRoomInfo;

	afx_msg void OnBnClickedBtnCreate();
	afx_msg void OnBnClickedBtnEnter();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	
	
};

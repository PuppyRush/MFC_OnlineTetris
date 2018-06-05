#pragma once


#include "afxdialogex.h"
#include "OnlineTetris.h"
#include "../Commons/structs.h"
#include "../Commons/Validator.h"
#include "CliektSocket.h"
#include "StringManager.h"

#include <regex>

class CMyDoc;
class CMyView;

class ServerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ServerDialog)
public:
	virtual ~ServerDialog();

protected:

	ServerDialog(CWnd* pParent = NULL);
	

	enum
	{
		IDD = _DLG_SERVER
	};

	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()
public:
//	CButton Edt_Create;
	CEdit Edt_Entername;
	CIPAddressCtrl Edt_Serverip;
	CEdit Edt_Servername;
	CEdit Edt_Serverport;

	string username;
	IPString ipstring;
	size_t portnum;

public:

	static shared_ptr<ServerDialog> GetDialog()
	{
		static auto dlg = shared_ptr<ServerDialog>(new ServerDialog());
		return dlg;
	}

	afx_msg void OnBnClickedBtnEnter();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	
	
};

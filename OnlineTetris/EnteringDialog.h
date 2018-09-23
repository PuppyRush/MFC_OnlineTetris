#pragma once


#include "afxdialogex.h"
#include "OnlineTetris.h"
#include "../Commons/structs.h"
#include "../Commons/Validator.h"
#include "TClientSocket.h"
#include "StringManager.h"
#include "WaitingRoomDialog.h"

#include <regex>

class CMyDoc;
class CMyView;

class EnteringDialog : public CDialogEx
{
	DECLARE_DYNAMIC(EnteringDialog)
public:
	virtual ~EnteringDialog();

protected:

	EnteringDialog(CWnd* pParent = NULL);
	

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

	static shared_ptr<EnteringDialog> GetDialog()
	{
		static auto dlg = shared_ptr<EnteringDialog>(new EnteringDialog());
		return dlg;
	}

	afx_msg void OnBnClickedBtnEnter();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	
private:
	
	void _RunWaitDialog();

};

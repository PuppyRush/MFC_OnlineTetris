#pragma once


// CMyEdit

class CMainFrame;
class CMyView;
class CMyDoc;

class CMyEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit)

public:

	CMyDoc::SEND_MESSAGE msg;
	CMainFrame *pMF;
	CMyView *pView;
	CMyDoc *pDoc;

public:
	CMyEdit();
	virtual ~CMyEdit();
	CString GetEditText();
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};



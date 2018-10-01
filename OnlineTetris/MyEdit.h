#pragma once


// CMyEdit

class CMainFrame;
class CMyView;
class CMyDoc;

class CChatEdit : public CEdit
{
	DECLARE_DYNAMIC(CChatEdit)

public:
	CChatEdit();
	virtual ~CChatEdit();
	CString GetEditText();
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};



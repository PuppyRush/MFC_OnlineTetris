
// MyView.h : CMyView Ŭ������ �������̽�
//

#pragma once

#include "..\Commons\structs.h"
#include "..\Commons\Entity\TUser.h"

class CMyDoc;
class EnteringDialog;
class CMyEdit;
class OptionDialog;
class CMyButton;

class CMyView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMyView();
	DECLARE_DYNCREATE(CMyView)

// Ư���Դϴ�.
public:
	CMyDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	
	//mSendReady send_ready;
	//mSendStartsignal send_start;
	//mSendMapstate send_map;

	CMyButton *Btn_Start;
	CMyButton *Btn_Ready;
	CEdit Edt_ChatEdit;

	TetrisUser *ME;
	CMyEdit *Edt_InputEdit;
	CListBox Lst_EnterList;
	CMyDoc *pDoc;
	OptionDialog *pOptionDlg;

	CBrush DeadBrush;
	CBrush BkBrush;
	CBrush HoleBrush;
	CRect GameRect[MAX_ENTER+1];
	CRect WinRect;
	CPen Mainpen, Subpen;
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	void ReadyBtnClicked();
	void StartBtnClicked();
	virtual void OnInitialUpdate();
	afx_msg void OnMenuServer();
	afx_msg void OnUpdateMenuServer(CCmdUI *pCmdUI);

	void VirtualDraw();
	void DrawImage(CDC *);
	void MessageHandler(const USER_MSG msg);
	
	bool CreateFigure();
	void SetGameover();
	void SetMap(int );
	void SetFigure();
	void SetGhostFigure();
	void MoveToDown();
	void MoveToGhostDown();
	void MoveToLeft();
	void MoveToRight();
	bool CheckLineDestroy();
	void AddLine(int );
	bool CheckDup(FIGURE backup);
	void ProcessMapState(mMapstate *map);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	afx_msg void OnBgm();
	afx_msg void OnUpdateBgm(CCmdUI *pCmdUI);
	afx_msg void On32800();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#ifndef _DEBUG  // MyView.cpp�� ����� ����
inline CMyDoc* CMyView::GetDocument() const
   { return reinterpret_cast<CMyDoc*>(m_pDocument); }
#endif


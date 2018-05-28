#pragma once


// OptionDialog 대화 상자입니다.

class CMyDoc;
class OptionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(OptionDialog)

public:
	OptionDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~OptionDialog();

// 대화 상자 데이터입니다.
	enum { IDD = _OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CMyDoc *pDoc;
	CComboBox Cmb_level;
	CComboBox Cmb_map;
	afx_msg void OnBnClickedOk();
	CComboBox Cmb_Bgm;
	CButton CHK_Ghost;
//	CButton Chk_Graviry;
	CButton Chk_Gravity;
};

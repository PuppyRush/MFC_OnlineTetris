#pragma once


// OptionDialog ��ȭ �����Դϴ�.

class CMyDoc;
class OptionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(OptionDialog)

public:
	OptionDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~OptionDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = _OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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

#pragma once

#include "../Commons/Entity/Room/TIRoom.h"

class CMyDoc;
class OptionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(OptionDialog)

public:
	
	virtual BOOL OnInitDialog();
	CComboBox m_cmb_level;
	CComboBox m_cmb_map;
	afx_msg void OnBnClickedOk();
	CButton m_chk_Ghost;
	//	CButton Chk_Graviry;
	CButton m_chk_Gravity;
	CComboBox m_cmb_usercount;

	TIRoom::property_level m_level;
	TIRoom::property_map m_map;
	size_t m_usercount;
	
	bool m_ghost;
	bool m_gravity;

	virtual ~OptionDialog();

	static auto getDialog()
	{
		static auto dlg = tetris::t_ptr< OptionDialog>(new OptionDialog());
		return dlg;
	}

	enum { IDD = _OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

private:
	OptionDialog(CWnd* pParent = NULL);
};

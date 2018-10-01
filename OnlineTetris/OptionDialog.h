#pragma once

#include "../Commons/Entity/Room/TIRoom.h"

class CMyDoc;
class CreateRoomDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CreateRoomDialog)

public:
	
	virtual BOOL OnInitDialog();
	CComboBox m_cmb_level;
	CComboBox m_cmb_map;
	afx_msg void OnBnClickedOk();
	CButton m_chk_Ghost;
	//	CButton Chk_Graviry;
	CButton m_chk_Gravity;
	CComboBox m_cmb_usercount;

	string m_roomname;
	TIRoom::property_level m_level;
	TIRoom::property_map m_map;
	size_t m_usercount;
	
	bool m_ghost;
	bool m_gravity;

	virtual ~CreateRoomDialog();

	static auto getDialog()
	{
		static auto dlg = tetris::t_ptr< CreateRoomDialog>(new CreateRoomDialog());
		return dlg;
	}

	enum { IDD = _DLG_CREATEROOM};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

private:
	CreateRoomDialog(CWnd* pParent = NULL);
public:
	CEdit m_edt_roomname;
};

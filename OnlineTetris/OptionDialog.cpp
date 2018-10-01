// OptionDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "OptionDialog.h"
#include "afxdialogex.h"

#include "StringManager.h"
#include "../Commons/Entity/Room/TIGameRoom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// OptionDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CreateRoomDialog, CDialogEx)

CreateRoomDialog::CreateRoomDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CreateRoomDialog::IDD, pParent)
{

}

CreateRoomDialog::~CreateRoomDialog()
{
}

void CreateRoomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, _CMB_LEVEL, m_cmb_level);
	DDX_Control(pDX, _CMB_MAP, m_cmb_map);
	DDX_Control(pDX, _GHOST, m_chk_Ghost);
	//  DDX_Control(pDX, CHK_GRAVITY, Chk_Graviry);
	DDX_Control(pDX, CHK_GRAVITY, m_chk_Gravity);
	DDX_Control(pDX, _CMB_USERCOUNT, m_cmb_usercount);
	DDX_Control(pDX, _EDT_ROOMNAME, m_edt_roomname);
}


BEGIN_MESSAGE_MAP(CreateRoomDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CreateRoomDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// OptionDialog �޽��� ó�����Դϴ�.


BOOL CreateRoomDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	auto it = EnumIterator<TIRoom::property_map>();
	for (it.begin(); it.end(); ++it)
	{
		switch (it.value)
		{
		case TIRoom::property_map::pyramid:
			m_cmb_map.AddString(_T("pyramid"));
			break;
		case TIRoom::property_map::rainfall:
			m_cmb_map.AddString(_T("rainfall"));
			break;
		case TIRoom::property_map::stairway:
			m_cmb_map.AddString(_T("stairway"));
			break;
		case TIRoom::property_map::straight:
			m_cmb_map.AddString(_T("straight"));
			break;
		case TIRoom::property_map::random:
			m_cmb_map.AddString(_T("random"));
			break;
		case TIRoom::property_map::empty:
			m_cmb_map.SetCurSel(toUType(it.value));
			m_cmb_map.AddString(_T("empty"));
			break;
		case TIRoom::property_map::arbitrary:
			m_cmb_map.AddString(_T("arbitrary"));
			break;
		default:
			assert(0);
		}
	}


	auto _it = EnumIterator<TIRoom::property_level>();
	for (_it.begin(); _it.end(); ++_it)
	{
		m_cmb_level.AddString(StringManager::ToCStringFrom(toUType(_it.value)+1));
	}
	m_cmb_level.SetCurSel(0);


	for(auto i= toUType(TIGameRoom::property::MinimunCount) ; i < toUType(TIGameRoom::property::MaxCount) ; i++)
		m_cmb_usercount.AddString(StringManager::ToCStringFrom(i));

	return TRUE;  
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CreateRoomDialog::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	auto sel = 1ull << (m_cmb_map.GetCurSel()+1);
	m_map = TIRoom::property_map(sel);

	sel = 1ull << (m_cmb_level.GetCurSel()+1);
	m_level = TIRoom::property_level(sel);

	m_ghost = m_chk_Ghost.GetCheck();
	m_gravity = m_chk_Gravity.GetCheck();
	m_usercount = m_cmb_usercount.GetCurSel() + toUType(TIGameRoom::property::MinimunCount);

	CString str;
	m_edt_roomname.GetWindowTextW(str);
	m_roomname = StringManager::ToStringFrom(str);

	CDialogEx::OnOK();
}

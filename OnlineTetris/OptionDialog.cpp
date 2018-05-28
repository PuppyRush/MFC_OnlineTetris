// OptionDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "OptionDialog.h"
#include "afxdialogex.h"
#include "MyDoc.h"

// OptionDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(OptionDialog, CDialogEx)

OptionDialog::OptionDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(OptionDialog::IDD, pParent)
{

}

OptionDialog::~OptionDialog()
{
}

void OptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, _CMB_LEVEL, Cmb_level);
	DDX_Control(pDX, _CMB_MAP, Cmb_map);
	DDX_Control(pDX, _GHOST, CHK_Ghost);
	//  DDX_Control(pDX, CHK_GRAVITY, Chk_Graviry);
	DDX_Control(pDX, CHK_GRAVITY, Chk_Gravity);
}


BEGIN_MESSAGE_MAP(OptionDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &OptionDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// OptionDialog �޽��� ó�����Դϴ�.


BOOL OptionDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	
	Cmb_map.AddString( _T("���"));
	Cmb_map.AddString( _T("�Ƕ�̵�"));
	Cmb_map.AddString( _T("�ҳ���"));
	Cmb_map.AddString( _T("����"));
	Cmb_map.AddString( _T("������(�ƹ����� ������)"));
	Cmb_map.AddString( _T("�ټ������� ����������"));
	Cmb_map.AddString( _T("����"));
	Cmb_map.AddString( _T("����"));

	Cmb_level.AddString( _T("1"));
	Cmb_level.AddString( _T("2"));
	Cmb_level.AddString( _T("3"));
	Cmb_level.AddString( _T("4"));
	Cmb_level.AddString( _T("5"));
	Cmb_level.AddString( _T("6"));
	Cmb_level.AddString( _T("7"));
	Cmb_level.AddString( _T("8"));
	Cmb_level.AddString( _T("9"));

	Cmb_map.SetCurSel(0);
	Cmb_level.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}




void OptionDialog::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int iiii=-1;
	iiii = Cmb_map.GetCurSel();

	pDoc->Map = iiii;

	iiii = Cmb_level.GetCurSel();

	pDoc->Level = iiii;

	pDoc->Ghost = CHK_Ghost.GetCheck();
	pDoc->Gravity = Chk_Gravity.GetCheck();

	CDialogEx::OnOK();
}

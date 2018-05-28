// OptionDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "OptionDialog.h"
#include "afxdialogex.h"
#include "MyDoc.h"

// OptionDialog 대화 상자입니다.

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


// OptionDialog 메시지 처리기입니다.


BOOL OptionDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	
	
	Cmb_map.AddString( _T("계단"));
	Cmb_map.AddString( _T("피라미드"));
	Cmb_map.AddString( _T("소낙비"));
	Cmb_map.AddString( _T("줄줄"));
	Cmb_map.AddString( _T("무작위(아무렇게 생성됨)"));
	Cmb_map.AddString( _T("다섯가지중 무작위선택"));
	Cmb_map.AddString( _T("시험"));
	Cmb_map.AddString( _T("없음"));

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
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}




void OptionDialog::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int iiii=-1;
	iiii = Cmb_map.GetCurSel();

	pDoc->Map = iiii;

	iiii = Cmb_level.GetCurSel();

	pDoc->Level = iiii;

	pDoc->Ghost = CHK_Ghost.GetCheck();
	pDoc->Gravity = Chk_Gravity.GetCheck();

	CDialogEx::OnOK();
}

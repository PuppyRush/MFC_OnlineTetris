// ServerDialog.cpp : 구현 파일입니다.
//

#include "StdAfx.h"
#include "EnteringDialog.h"
#include "../Commons/Validator.h"

// ServerDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(ServerDialog, CDialogEx)

ServerDialog::ServerDialog(CWnd* pParent /*=NULL*/)
	:CDialogEx(ServerDialog::IDD, pParent)
	, ipstring({ 0,0,0,0 })
{

}

ServerDialog::~ServerDialog()
{
}

void ServerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, _EDT_ENTERNAME, Edt_Entername);
	DDX_Control(pDX, _EDT_SERVERIP, Edt_Serverip);
	DDX_Control(pDX, _EDT_SERVERPORTNUM, Edt_Serverport);
}


BEGIN_MESSAGE_MAP(ServerDialog, CDialogEx)
	ON_BN_CLICKED(_BTN_ENTER, &ServerDialog::OnBnClickedBtnEnter)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// ServerDialog 메시지 처리기입니다.


//입장하기
void ServerDialog::OnBnClickedBtnEnter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString name;
	Edt_Entername.GetWindowTextW(name);
	string str_name = CSTRTCH(name);

	if (!validator::IdCheck(str_name,5,10))
		return;

	BYTE a1,a2,a3,a4;
	Edt_Serverip.GetAddress(a1, a2, a3, a4);
	IPString ipstring({ a1,a2,a3,a4 });
	
	CString str_portnum;
	Edt_Serverport.GetWindowTextW(str_portnum);
	size_t portnum = atoi(CSTRTCH(str_portnum));
	if (!(portnum >= 1000 && portnum <= 10000))
	{
		MessageBox(_T("포트는 1000~10000만 가능합니다"));
		return;
	}

	username = str_name;
	this->portnum = portnum;
	this->ipstring = ipstring;

	this->DestroyWindow();
}


BOOL ServerDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	Edt_Serverip.SetAddress( (BYTE)210, (BYTE)179, (BYTE)101, (BYTE)193);
	Edt_Serverport.SetWindowTextW(_T("5805"));
	Edt_Entername.SetWindowTextW( _T("Write_your_name"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ServerDialog::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CDialogEx::OnClose();
}


void ServerDialog::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	this->DestroyWindow();
	CDialogEx::PostNcDestroy();
}

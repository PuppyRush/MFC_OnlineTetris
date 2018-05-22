// ServerDialog.cpp : ���� �����Դϴ�.
//

#include "StdAfx.h"
#include "EnteringDialog.h"
#include "../Commons/Validator.h"

// ServerDialog ��ȭ �����Դϴ�.

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


// ServerDialog �޽��� ó�����Դϴ�.


//�����ϱ�
void ServerDialog::OnBnClickedBtnEnter()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		MessageBox(_T("��Ʈ�� 1000~10000�� �����մϴ�"));
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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	Edt_Serverip.SetAddress( (BYTE)210, (BYTE)179, (BYTE)101, (BYTE)193);
	Edt_Serverport.SetWindowTextW(_T("5805"));
	Edt_Entername.SetWindowTextW( _T("Write_your_name"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void ServerDialog::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//CDialogEx::OnClose();
}


void ServerDialog::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	this->DestroyWindow();
	CDialogEx::PostNcDestroy();
}

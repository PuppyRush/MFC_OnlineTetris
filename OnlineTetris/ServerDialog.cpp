// ServerDialog.cpp : ���� �����Դϴ�.
//

#include "StdAfx.h"
#include "ServerDialog.h"
#include "../Commons/Validator.h"

// ServerDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ServerDialog, CDialogEx)

ServerDialog::ServerDialog(CWnd* pParent /*=NULL*/)
	:CDialogEx(ServerDialog::IDD, pParent)
	,isValidationMakeRoomInfo(false)
	,isValidationEnterRoomInfo(false)
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
	DDX_Control(pDX, _EDT_SERVERNAME, Edt_Servername);
	DDX_Control(pDX, _EDT_ROOMNAME, Edt_Roomname);
	DDX_Control(pDX, _EDT_PORTNUM, Edt_Portnum);
}


BEGIN_MESSAGE_MAP(ServerDialog, CDialogEx)
	ON_BN_CLICKED(_BTN_CREATE, &ServerDialog::OnBnClickedBtnCreate)
	ON_BN_CLICKED(_BTN_ENTER, &ServerDialog::OnBnClickedBtnEnter)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// ServerDialog �޽��� ó�����Դϴ�.

//�����ϱ�
void ServerDialog::OnBnClickedBtnCreate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
    CString name;
	Edt_Servername.GetWindowTextW( name);
	if(name.GetLength()==0){
		MessageBox( _T("���̵� �Է��ϼ���"));
		return;
	}
	
	int len = WideCharToMultiByte(CP_ACP, 0, name, -1, NULL, 0, NULL, NULL);
	if(len>=ID_LEN){
		MessageBox( _T("���̵��� ���̴� ���� 1~10�� �ѱ� 1~5���Դϴ�"));
		return;
	}



	//TCP ������ �����ϰ� 7000�� ��Ʈ���� ������ ����Ѵ�.
 	//if(pDoc->m_serverSocket->Create(PORTNUM, SOCK_STREAM))
	//{
	//	if(pDoc->m_serverSocket->Listen())
	//	{
	//		
 	//		pView->MessageHandler(SUCC_SERVEROPEN);
	//		pDoc->Open = true;
	//		pDoc->Enter = false;
	//		pDoc->Name = name;
	//		pDoc->ServerIp = pDoc->GetServerIP();
	//		
	//		memcpy(pDoc->chName, pDoc->StringToChar( pDoc->Name), strlen(pDoc->StringToChar( pDoc->Name)));
	//		pDoc->CreateRoot();
	//
	//	}
	//	else
	//	{
	//		//����, �̹� �ش� ��Ʈ�� ����� ���α׷��� �ִٸ� �����Ѵ�.
	//		pView->MessageHandler(PREUSE_PORT);
	//		pDoc->Open = pDoc->Enter = false;
	//	}
	//}
	//else
	//{
	//	pView->MessageHandler(FAIL_SERVEROPEN);
	//	pDoc->Open = pDoc->Enter = false;
	//}

	isValidationMakeRoomInfo = true;
	this->DestroyWindow();
	
}

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
	IPString ipstring(initializer_list<size_t>{ a1,a2,a3,a4 });
	
	CString str_portnum;
	Edt_Portnum.GetWindowTextW(str_portnum);
	size_t portnum = atoi(CSTRTCH(str_portnum));
	if (!(portnum >= 1000 && portnum <= 10000))
	{
		MessageBox(_T("��Ʈ�� 1000~10000�� �����մϴ�"));
		return;
	}

	username = str_name;
	this->portnum = portnum;
	this->ipstring = ipstring;

	isValidationEnterRoomInfo = true;

//	bool res = pDoc->m_mySocket->Connect( pDoc->ServerIp, PORTNUM);

	/*if(res)
		pDoc->ProcessEnter(name);
	
	else{
		pView->MessageHandler( FAIL_SERVERCONN);
		pDoc->Open =pDoc->Enter = false;
		pDoc->m_mySocket->Close();
		delete pDoc->m_mySocket;
		pDoc->m_mySocket = NULL;
	}*/
	
	this->DestroyWindow();
}


BOOL ServerDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	Edt_Serverip.SetAddress( (BYTE)210, (BYTE)179, (BYTE)101, (BYTE)193);
	Edt_Portnum.SetWindowTextW(_T("5805"));
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

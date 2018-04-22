// ServerDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "OnlineTetris.h"

#include "MyDoc.h"
#include "MyView.h"
#include "MyListen.h"

#include "ServerDialog.h"
#include "afxdialogex.h"

#include "MySocket.h"
// ServerDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ServerDialog, CDialogEx)

ServerDialog::ServerDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(ServerDialog::IDD, pParent)
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
}


BEGIN_MESSAGE_MAP(ServerDialog, CDialogEx)
	ON_BN_CLICKED(_BTN_CREATE, &ServerDialog::OnBnClickedEdtCreate)
	ON_BN_CLICKED(_BTN_ENTER, &ServerDialog::OnBnClickedButton3)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// ServerDialog �޽��� ó�����Դϴ�.

//�����ϱ�
void ServerDialog::OnBnClickedEdtCreate()
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


	if(pDoc->pListen == NULL)
		pDoc->pListen = new CMyListen(pView,pDoc);

	//TCP ������ �����ϰ� 7000�� ��Ʈ���� ������ ����Ѵ�.
 	if(pDoc->pListen->Create(PORTNUM, SOCK_STREAM))
	{
		if(pDoc->pListen->Listen())
		{
			
 			pView->MessageHandler(SUCC_SERVEROPEN);
			pDoc->Open = true;
			pDoc->Enter = false;
			pDoc->Name = name;
			pDoc->ServerIp = pDoc->GetServerIP();
			
			memcpy(pDoc->chName, pDoc->StringToChar( pDoc->Name), strlen(pDoc->StringToChar( pDoc->Name)));
			pDoc->CreateRoot();

		}
		else
		{
			//����, �̹� �ش� ��Ʈ�� ����� ���α׷��� �ִٸ� �����Ѵ�.
			pView->MessageHandler(PREUSE_PORT);
			pDoc->Open = pDoc->Enter = false;
		}
	}
	else
	{
		pView->MessageHandler(FAIL_SERVEROPEN);
		pDoc->Open = pDoc->Enter = false;
	}

	this->DestroyWindow();
	
}

//�����ϱ�
void ServerDialog::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString name;
	Edt_Entername.GetWindowTextW(name);
	if(name.GetLength()==0){
		MessageBox( _T("���̵� �Է��ϼ���"));
		return;
	}
	int len = WideCharToMultiByte(CP_ACP, 0, name, -1, NULL, 0, NULL, NULL);
	if(len>=ID_LEN){
		MessageBox( _T("���̵��� ���̴� ���� 1~10�� �ѱ� 1~5���Դϴ�"));
		return;
	}

	Edt_Entername.GetWindowTextW( name);

	BYTE a1,a2,a3,a4;

	Edt_Serverip.GetAddress(a1,a2,a3,a4);
	pDoc->ServerIp.Format( _T("%d.%d.%d.%d"), a1,a2,a3,a4);

	if( pDoc->MySocket != NULL || pDoc == NULL || pView == NULL){
		if(pView != NULL)
			pView->MessageHandler(-1);
		return;
	}
		
	pDoc->MySocket = new CMySocket;
	pDoc->MySocket->Create();
	pDoc->MySocket->pDoc = pDoc;
	pDoc->MySocket->pView = pView;
	
	bool res = pDoc->MySocket->Connect( pDoc->ServerIp, PORTNUM);

	if(res)
		pDoc->ProcessEnter(name);
	
	else{
		pView->MessageHandler( FAIL_SERVERCONN);
		pDoc->Open =pDoc->Enter = false;
		pDoc->MySocket->Close();
		delete pDoc->MySocket;
		pDoc->MySocket = NULL;
	}
	
	this->DestroyWindow();
}


BOOL ServerDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	Edt_Serverip.SetAddress( (BYTE)127, (BYTE)0, (BYTE)0, (BYTE)1);
	Edt_Entername.SetWindowTextW( _T("ENTER"));
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
	pView->pServerDlg = NULL;
	this->DestroyWindow();

	CDialogEx::PostNcDestroy();
}

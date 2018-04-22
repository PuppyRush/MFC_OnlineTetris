// ServerDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OnlineTetris.h"

#include "MyDoc.h"
#include "MyView.h"
#include "MyListen.h"

#include "ServerDialog.h"
#include "afxdialogex.h"

#include "MySocket.h"
// ServerDialog 대화 상자입니다.

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


// ServerDialog 메시지 처리기입니다.

//개설하기
void ServerDialog::OnBnClickedEdtCreate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
    CString name;
	Edt_Servername.GetWindowTextW( name);
	if(name.GetLength()==0){
		MessageBox( _T("아이디를 입력하세요"));
		return;
	}
	
	int len = WideCharToMultiByte(CP_ACP, 0, name, -1, NULL, 0, NULL, NULL);
	if(len>=ID_LEN){
		MessageBox( _T("아이디의 길이는 영어 1~10자 한글 1~5자입니다"));
		return;
	}


	if(pDoc->pListen == NULL)
		pDoc->pListen = new CMyListen(pView,pDoc);

	//TCP 소켓을 생성하고 7000번 포트에서 연결을 대기한다.
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
			//만일, 이미 해당 포트를 열어둔 프로그램이 있다면 실패한다.
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

//입장하기
void ServerDialog::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString name;
	Edt_Entername.GetWindowTextW(name);
	if(name.GetLength()==0){
		MessageBox( _T("아이디를 입력하세요"));
		return;
	}
	int len = WideCharToMultiByte(CP_ACP, 0, name, -1, NULL, 0, NULL, NULL);
	if(len>=ID_LEN){
		MessageBox( _T("아이디의 길이는 영어 1~10자 한글 1~5자입니다"));
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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	Edt_Serverip.SetAddress( (BYTE)127, (BYTE)0, (BYTE)0, (BYTE)1);
	Edt_Entername.SetWindowTextW( _T("ENTER"));
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
	pView->pServerDlg = NULL;
	this->DestroyWindow();

	CDialogEx::PostNcDestroy();
}

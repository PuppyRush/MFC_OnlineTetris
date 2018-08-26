// ServerDialog.cpp : 구현 파일입니다.
//

#include "StdAfx.h"
#include "EnteringDialog.h"
#include "ConnectingDialog.h"

#include "../Commons/TSocketThread.h"
#include "../Commons/TObjectContainerFactory.h"
#include "../Commons/Validator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(EnteringDialog, CDialogEx)

EnteringDialog::EnteringDialog(CWnd* pParent /*=NULL*/)
	:CDialogEx(EnteringDialog::IDD, pParent)
	, ipstring({ 0,0,0,0 })
{

}

EnteringDialog::~EnteringDialog()
{
}

void EnteringDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, _EDT_ENTERNAME, Edt_Entername);
	DDX_Control(pDX, _EDT_SERVERIP, Edt_Serverip);
	DDX_Control(pDX, _EDT_SERVERPORTNUM, Edt_Serverport);
}


BEGIN_MESSAGE_MAP(EnteringDialog, CDialogEx)
	ON_BN_CLICKED(_BTN_ENTER, &EnteringDialog::OnBnClickedBtnEnter)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// ServerDialog 메시지 처리기입니다.


//입장하기
void EnteringDialog::OnBnClickedBtnEnter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString name;
	Edt_Entername.GetWindowTextW(name);
	string str_name = StringManager::ToStringFrom(name);

	if (!idCheck(str_name,5,10))
		return;

	BYTE a1,a2,a3,a4;
	Edt_Serverip.GetAddress(a1, a2, a3, a4);
	IPString ipstring({ a1,a2,a3,a4 });
	
	CString str_portnum;
	Edt_Serverport.GetWindowTextW(str_portnum);

	size_t portnum = atoi(StringManager::ToStringFrom(str_portnum).c_str());
	if (!(portnum >= 1000 && portnum <= 10000))
	{
		MessageBox(_T("포트는 1000~10000만 가능합니다"));
		return;
	}

	username = str_name;

	TClientUser::get()->setName(username);

	this->portnum = portnum;
	this->ipstring = ipstring;

	shared_ptr<TClientSocket> socket = TClientSocket::get();
	//ConnectingDialog conDlg;
	//conDlg.Create(IDD_CONNECTING);

	//while (!socket->isConnected())
	//{
		if (socket->create(ipstring, portnum) == 0)
		{
			auto socketThread = TSocketThread::get();
			socketThread->run();

			const auto me = TClientUser::get();

			TObjectContainerFactory::get()->getSocketContainer()->add(socket->getUnique(), socket);
			TObjectContainerFactory::get()->getUserContainer()->add(me->getUnique(), me);
			
			const auto header = Header(toUType(Priority::Normal), toUType(SERVER_MSG::CONNECTION_INFO));
			const mSendName sendname(header, me->getUserName().size(), me->getUserName().c_str());

			socket->pushMessage(&sendname);

			if (WaitingRoomDlg::GetDialog()->DoModal() == IDOK)
			{
				socket->SelfClose();
			}

			//conDlg.CloseWindow();
		}
		else
		{
			//conDlg.ShowWindow(SW_SHOW);
			//AfxMessageBox(_T("Cant Connect to server. check written your ip and port"));
			socket->SelfClose();
		}
	//}
	CDialogEx::OnOK();
}


BOOL EnteringDialog::OnInitDialog()  
{
	CDialogEx::OnInitDialog();

	Edt_Serverip.SetAddress( (BYTE)210, (BYTE)179, (BYTE)101, (BYTE)193);
	Edt_Serverport.SetWindowTextW(_T("5905"));
	Edt_Entername.SetWindowTextW( _T("your_name"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void EnteringDialog::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
}


void EnteringDialog::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	this->DestroyWindow();
	CDialogEx::PostNcDestroy();
}

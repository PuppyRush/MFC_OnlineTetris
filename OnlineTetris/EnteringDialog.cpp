// ServerDialog.cpp : ���� �����Դϴ�.
//

#include "StdAfx.h"
#include "EnteringDialog.h"
#include "ConnectingDialog.h"

#include "../Commons/TMessageThread.h"
#include "../Commons/TObjectContainerFactory.h"
#include "../Commons/Validator.h"
#include "../Commons/TMessageSender.h" 
#include "TWaitingRoom.h"

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


// ServerDialog �޽��� ó�����Դϴ�.


//�����ϱ�
void EnteringDialog::OnBnClickedBtnEnter()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		MessageBox(_T("��Ʈ�� 1000~10000�� �����մϴ�"));
		return;
	}

	username = str_name;

	TClientUser::get()->setName(username);

	this->portnum = portnum;
	this->ipstring = ipstring;

	const auto waitfn = &EnteringDialog::_RunWaitDialog;
	auto wiat_th = make_shared<thread>(waitfn, this);

	shared_ptr<TClientSocket> socket = TClientSocket::get();
	while (!socket->isConnected())
	{
		if (socket->create(ipstring, portnum) == 0)
		{
			ConnectingDialog::GetDialog()->CloseWindow();

			auto socketThread = TMessageThread::get();
			socketThread->run();

			auto me = TClientUser::get();
			TObjectContainerFactory::get()->getContainer<TIWaitingRoom>(property_distinguish::WaitingRoom)->add(TWaitingRoom::get());
			TObjectContainerFactory::get()->getContainer<TetrisSocket>(property_distinguish::Socket)->add(socket);
			TObjectContainerFactory::get()->getContainer<TetrisUser>(property_distinguish::User)->add(me);


			if (WaitingRoomDlg::getDialog()->DoModal() == IDOK)
			{
				socket->SelfClose();
			}

			break;
		}
		else
		{
			socket->SelfClose();
		}
	}

	CDialogEx::OnOK();
}


BOOL EnteringDialog::OnInitDialog()  
{
	CDialogEx::OnInitDialog();

	Edt_Serverip.SetAddress( (BYTE)210, (BYTE)179, (BYTE)101, (BYTE)193);
	Edt_Serverport.SetWindowTextW(_T("5905"));
	Edt_Entername.SetWindowTextW( _T("your_name"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void EnteringDialog::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnClose();
}


void EnteringDialog::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	this->DestroyWindow();
	CDialogEx::PostNcDestroy();
}


void EnteringDialog::_RunWaitDialog()
{
	
	auto conDlg = ConnectingDialog::GetDialog();
	conDlg->DoModal();
	//conDlg->Create(IDD_CONNECTING);
	//conDlg->ShowWindow(SW_SHOW);
}
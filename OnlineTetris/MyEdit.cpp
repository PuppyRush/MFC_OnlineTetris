// MyEdit.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "MyEdit.h"
#include "MyDoc.h"
#include "MyView.h"
#include "MainFrm.h"
#include "TClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{}

CMyEdit::~CMyEdit()
{}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
END_MESSAGE_MAP()



// CMyEdit �޽��� ó�����Դϴ�.




BOOL CMyEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		//Ư���� �������� ä��â�ΰ��
		if(GetFocus()->GetDlgCtrlID() == 1001)
		{
			const auto pMF = (CMainFrame *)AfxGetMainWnd();
			const auto pDoc = (CMyDoc *)pMF->GetActiveDocument();
			const auto pView = (CMyView *)pMF->GetActiveView();

			if(GetWindowTextLengthW() == 0)
				return false;
			else if(!TClientSocket::get()->isConnected())
			{
				pView->MessageHandler(USER_MSG::NOT_OPENNENTER);
				return false;
			}
			else if(!TClientSocket::get()->isConnected())
			{
				char chat[MSG_LEN];
				char temp[MSG_LEN];

				//ä��â�� �Է��Ѱ� temp�� �ű��
				CString str = GetEditText();
				int len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, str, -1, temp, len, NULL, NULL);

				//ä���� ������ �ԷµǸ� ���� �ڵ����� ������
				if(strstr(temp, "����") != NULL)
					pView->ReadyBtnClicked();

				//�̸��� chat�� �����´�
				str = CString(pDoc->m_name.c_str());
				len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, str, -1, chat, len, NULL, NULL);

				strcat(chat, " : ");
				strcat(chat, temp);

				mMessage msg(Header( toUType( Priority::Normal), toUType(CLIENT_MSG::SEND_MESSAGE)), strlen(chat), chat);
				//TClientSocket::get()->pushMessage(&msg);
				Sleep(50);
			}
		}
		this->SetWindowTextW(_T(""));
	}

	return CEdit::PreTranslateMessage(pMsg);
}

CString CMyEdit::GetEditText()
{

	CString str;
	this->GetWindowTextW(str);
	return str;


}
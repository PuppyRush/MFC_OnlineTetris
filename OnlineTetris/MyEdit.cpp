// MyEdit.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "MyEdit.h"
#include "MyDoc.h"
#include "MyView.h"
#include "MainFrm.h"
#include "CliektSocket.h"

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
			else if(pDoc->Open == false && pDoc->Enter == false)
			{
				pView->MessageHandler(NOT_OPENNENTER);
				return false;
			}
			else if(pDoc->Open || pDoc->Enter)
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
				str = CString(pDoc->Name.c_str());
				len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, str, -1, chat, len, NULL, NULL);

				strcat(chat, " : ");
				strcat(chat, temp);

				mSendMessage msg(Header(SEND_MESSAGE), strlen(chat), chat);
				pDoc->m_mySocket->Send((char *)&msg, sizeof(msg));
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
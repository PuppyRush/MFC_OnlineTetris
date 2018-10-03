// MyEdit.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "MyEdit.h"
#include "TClientSocket.h"
#include "StringManager.h"

#include "../Commons/TMessageObject.h"
#include "../Commons/TMessageSender.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CMyEdit

IMPLEMENT_DYNAMIC(CChatEdit, CEdit)

CChatEdit::CChatEdit()
{}

CChatEdit::~CChatEdit()
{}


BEGIN_MESSAGE_MAP(CChatEdit, CEdit)
END_MESSAGE_MAP()


BOOL CChatEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetWindowTextLengthW() == 0)
			return false;

		char temp[MSG_LEN];

		//ä��â�� �Է��Ѱ� temp�� �ű��
		CString str = this->GetEditText();

		switch (m_chatType)
		{
		case TChat::property_chat::SendMsg:
			TClientUser::get()->sendChatMessage(StringManager::ToStringFrom(str));
			break;
		case TChat::property_chat::SendWhisper:
			TClientUser::get()->sendWhisperMessage(m_whispee, StringManager::ToStringFrom(str));
			break;
		default:
			assert(0);
		}
		
		//ä���� ������ �ԷµǸ� ���� �ڵ����� ������
		//if(strstr(temp, "����") != NULL)
		//	pView->ReadyBtnClicked();

		
		//Sleep(50);
		this->SetWindowTextW(_T(""));
	}

	return CEdit::PreTranslateMessage(pMsg);
}

CString CChatEdit::GetEditText()
{
	CString str;
	this->GetWindowTextW(str);
	return str;
}


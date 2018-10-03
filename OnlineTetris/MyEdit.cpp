// MyEdit.cpp : 구현 파일입니다.
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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetWindowTextLengthW() == 0)
			return false;

		char temp[MSG_LEN];

		//채팅창에 입력한걸 temp에 옮긴다
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
		
		//채팅중 ㄱㄱ가 입력되면 레디를 자동으로 누른다
		//if(strstr(temp, "ㄱㄱ") != NULL)
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


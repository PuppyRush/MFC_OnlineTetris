// MyEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "MyEdit.h"
#include "MyDoc.h"
#include "MyView.h"
#include "MainFrm.h"
#include "MySocket.h"

// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{
	pDoc = NULL;
	pView = NULL;
	pMF = NULL;
}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
END_MESSAGE_MAP()



// CMyEdit 메시지 처리기입니다.




BOOL CMyEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN){

		//특별히 메인폼의 채팅창인경우
		if( GetFocus()->GetDlgCtrlID() == 1001 ){

			
			pMF = (CMainFrame *)AfxGetMainWnd();
			pDoc = (CMyDoc *)pMF->GetActiveDocument();
			pView = (CMyView *)pMF->GetActiveView();

			if(GetWindowTextLengthW() ==0)
				return false;
			else if(pDoc->Open==false && pDoc->Enter==false ){
				pView->MessageHandler(NOT_OPENNENTER);
				return false;
			}
			else if( pDoc->Open || pDoc->Enter){
				char chat[MSG_LEN];
				char temp[MSG_LEN];
				memset( &msg, 0, sizeof(msg));

						
				
				//채팅창에 입력한걸 temp에 옮긴다
				CString str =  GetEditText();
				int len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, str, -1, temp, len, NULL, NULL);	
		
				//채팅중 ㄱㄱ가 입력되면 레디를 자동으로 누른다
				if(strstr( temp, "ㄱㄱ") != NULL)
					pView->ReadyBtnClicked();

				//이름을 chat에 가져온다
				str = pDoc->Name;
				len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, str, -1, chat, len, NULL, NULL);
	
				
				strcat(chat, " : ");			
				strcat(chat, temp);

				msg.IsServer = true;
				memcpy( &msg.msg, chat, sizeof(chat));
				msg.msglen = sizeof(chat);
				msg.msg_idx = SEND_MESSAGE;
				msg.struct_size = sizeof( msg);
				
				
				pDoc->MySocket->Send( (char *)&msg, sizeof(msg));
				Sleep(50);
		
			}
			
		}
		this->SetWindowTextW( _T(""));
	}


	return CEdit::PreTranslateMessage(pMsg);
}

CString CMyEdit::GetEditText(){

	CString str;
	this->GetWindowTextW(str);
	return str;


}
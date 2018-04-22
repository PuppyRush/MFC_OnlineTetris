
// MyDoc.cpp : CMyDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "OnlineTetris.h"
#endif

#include "MyDoc.h"
#include "MyListen.h"
#include "MySocket.h"
#include "MyButton.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyDoc

IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
END_MESSAGE_MAP()


// CMyDoc 생성/소멸

CMyDoc::CMyDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	srand((unsigned)time(NULL));
	End = Ready = Open = Enter = Start = false;
	pListen = NULL;
	MySocket= NULL;
	memset( chName, 0, ID_LEN);
	Map = Level = 1;
	Bgm = true;
	LineRemain  =0 ;
}

CMyDoc::~CMyDoc()
{
}

BOOL CMyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.


	return TRUE;
}




// CMyDoc serialization

void CMyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMyDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMyDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMyDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMyDoc 진단

#ifdef _DEBUG
void CMyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyDoc 명령


char *CMyDoc::StringToChar(const CString& str){

	char name[ID_LEN]={0};

	int len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, str, -1, name, len, NULL, NULL);

	return name;

}

//////////////////////서버 함수///////////////////////
//서버 ip얻기
CString CMyDoc::GetServerIP(){
	 
	WORD wVersionRequested;
    WSADATA wsaData;
    char name[255];
    CString ip; 
    PHOSTENT hostinfo;
    wVersionRequested = MAKEWORD( 2, 0 );
    if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
    {
        if( gethostname ( name, sizeof(name)) == 0)
        {
            if((hostinfo = gethostbyname(name)) != NULL)
            {
                ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
            }
        }     
        WSACleanup( );
    }

	return ip;
}

//서버함수
CMySocket* CMyDoc::NameToSocket(CString name){

	TUser *tmp;
	POSITION pos = Server_UserList.GetHeadPosition();
	while(pos != NULL){

		tmp = (TUser  *)Server_UserList.GetNext(pos);
		if( (CMySocket *)tmp->GetUserName().Compare(name) == 0){

			return tmp->GetSocket();		
			break;
		}
	}

	return NULL;

}
//서버함수
TUser* CMyDoc::NameToTUser(CString name){

	TUser *tmp;
	POSITION pos = Server_UserList.GetHeadPosition();
	while(pos != NULL){

		tmp = (TUser  *)Server_UserList.GetNext(pos);
		if( (CMySocket *)tmp->GetUserName().Compare(name) == 0){

			return tmp;		
			break;
		}
	}

	return NULL;
}

TUser *CMyDoc::SocketToTUser(CMySocket *soc){

	TUser *tmp;
	POSITION pos = Server_UserList.GetHeadPosition();
	while(pos != NULL){

		tmp = (TUser  *)Server_UserList.GetNext(pos);
		if( tmp->GetSocket() == soc){

			return tmp;		
			break;
		}
	}

	return NULL;

}

bool CMyDoc::ExistUser(CString name){

	POSITION pos = Client_UserList.GetHeadPosition();
	TUser *user = NULL;

	while(pos != NULL){

		user = (TUser *)Client_UserList.GetNext(pos);
		if(user == NULL)
			continue;
		if(user->GetUserName().Compare(name) == 0)
			return true;

	}

	return false;
}

void CMyDoc::CreateRoot(){

	//서버도 하나의 클라이언트로 취급하여 게임을 하는 모든 유저에 대해 일관성있게 처리 할 수 있게 한다.
	if(MySocket == NULL)
		MySocket = new CMySocket();

	MySocket->pView = pView;
	MySocket->pDoc = this;
	MySocket->Create();
	MySocket->Connect( ServerIp, PORTNUM);
	
	TUser *tmp = new TUser(Name);
	Client_UserList.AddTail(tmp);
	pView->ME = tmp;

	if(!MySocket->Sendname(chName, strlen(chName)))
		pView->MessageHandler(FAIL_SENDMSG);

	Enter = false;
	Open = true;
}


bool CMyDoc::Adduser(char *name, int namelen, CMySocket *soc){

	int num=0;
	CString temp;
	CString str( name, namelen);
	for(int i=0 ; i < Server_EnterUsers.GetCount() ; i++){
		if( Server_EnterUsers[i].Compare( str) ==0 ){
			SEND_PERMIT send_per;
			memset(&send_per, 0, sizeof(send_per));
			send_per.IsServer = false;
			send_per.msg_idx = FAIL_ENTER;
			send_per.res = DUP_ID;
			soc->Send( (char *)&send_per, sizeof(send_per));
			return false;
		}
	}

	TUser *usr = SocketToTUser(soc);
	if( usr != NULL){
		usr->SetName(str);					
		Server_EnterUsers.Add(str);
	}
	else
		pView->MessageHandler(-1);

	return true;
}


//클라이언트함수

TUser *CMyDoc::Client_NameToTUser(CString name){

	TUser *tmp = NULL;
	POSITION pos = Client_UserList.GetHeadPosition();
	while(pos != NULL){

		tmp = (TUser  *)Client_UserList.GetNext(pos);
		if( (CMySocket *)tmp->GetUserName().Compare(name) == 0){

			return tmp;		
			break;
		}
	}

	return NULL;

}

void CMyDoc::AddChat(char *msg, int msglen){

	CString str(msg, msglen);
	ChatLog +=( _T("\r\n") + str);
	pView->Edt_ChatEdit.SetWindowTextW(ChatLog);

}

//방에 접속하면 서버에서 이름들을 보냄.
//현재 방에 입장해 있는사람들을 점검하기 위함.
void CMyDoc::SetEnterUsers(CMyDoc::ON_NAMES names){

	POSITION pos= Client_UserList.GetHeadPosition();
	TUser *user = NULL, *temp = NULL;
	bool nothing = true;

	Client_EnterUsers.RemoveAll();
	pView->Lst_EnterList.ResetContent();

	for(int i=0 ; i < names.enternum ; i++){
		CString name( names.name[i] , names.namelen[i]);
		
		//클라이언트에 이미 생성된 유저라면 유저객체를 만들지 않는다.
		//없는것이 판단되면 새로 생성
		if( !ExistUser(name)){
			temp = new TUser(name);

			Client_UserList.AddTail(temp);
		}		

		Client_EnterUsers.Add(name);
		
		temp = NULL;
		pos =  Client_UserList.GetHeadPosition();
		nothing= true;
	}
	
	ME = Client_NameToTUser(Name);
	pView->ME = ME;
	if(ME==NULL){
		pView->MessageHandler(FAIL_FINDNAME);
		return;
	}
	
}

void CMyDoc::SetReady(CMyDoc::ON_READIES rdy){

	TUser *user = NULL;
	int rdynum=0;
	for(int i=0 ; i < rdy.enternum ; i++){
		CString name(rdy.name[i], rdy.namelen[i]);

		user = Client_NameToTUser(name);
		if(user == NULL){
			pView->MessageHandler(FAIL_FINDNAME);
			continue;
		}
		user->SetReady( rdy.ready[i]);

		if( user->GetReady())
			rdynum++;
	}
	
	if(rdynum == Client_EnterUsers.GetCount() && Open )
		pView->Btn_Start->EnableWindow(true);
	else if( Open)
		pView->Btn_Start->EnableWindow(false);

	pView->VirtualDraw();
}

void CMyDoc::SetOrder(){

	TUser *user = NULL;
	
	for(int i=0 ; i < Client_EnterUsers.GetCount() ; i++){
		user = Client_NameToTUser( Client_EnterUsers[i]);
		if(user == NULL){
			pView->MessageHandler(FAIL_FINDNAME);
			continue;
		}
		user->SetOrder(i+1);
		pView->Lst_EnterList.AddString( Client_EnterUsers[i] );
	}

	//클라이언트(서버포함) 자신을 순서를 1로 변경한다.
	if( Client_NameToTUser(Name)->GetOrder()!= 1){
		int idx = Client_NameToTUser( Name )->GetOrder();
		Client_NameToTUser( Name )->SetOrder(1);
		for(int i=0 ; i < Client_EnterUsers.GetCount() ; i++)
			if( Client_NameToTUser( Client_EnterUsers[i] )->GetOrder() == 1){
				Client_NameToTUser( Client_EnterUsers[i] )->SetOrder(idx);
				break;
			}
	}

	pView->VirtualDraw();

}

void CMyDoc::ProcessEnter(CString name){

	Open = false;
	Enter = true;
	Name = name;
	memcpy(chName, StringToChar( Name), strlen(StringToChar( Name)));
	
	TUser *tmp = new TUser(Name);
	Client_UserList.AddTail(tmp);

	if(!MySocket->Sendname(chName, strlen( chName) ))
		pView->MessageHandler(FAIL_SENDMSG);

	pView->Btn_Start->EnableWindow(false);

}

void CMyDoc::ProcessClose(){

	Enter = Open = false;

	pView->MessageHandler(CLOSE_SERVER);

}

//서버가 시작신호를 보내면 클라인트에선 시작을 위한 처리를 한다.
void CMyDoc::Client_ProcessStart(ON_STARTSIGNAL on_start){

	Ghost = on_start.ghost;
	pView->SetMap(on_start.map);
	Start = true;
	switch(on_start.level){
		case 0:
			pView->SetTimer(TIMER_TETRIS, 1700, NULL);
			break;
		case 2:
			pView->SetTimer(TIMER_TETRIS, 1300, NULL);
			break;
		case 3:
			pView->SetTimer(TIMER_TETRIS, 1000, NULL);
			break;
		case 4:
			pView->SetTimer(TIMER_TETRIS, 800, NULL);
			break;
		case 5:
			pView->SetTimer(TIMER_TETRIS, 600, NULL);
			break;
		case 6:
			pView->SetTimer(TIMER_TETRIS, 400, NULL);
			break;
		case 7:
			pView->SetTimer(TIMER_TETRIS, 200, NULL);
			break;
		case 8:
			pView->SetTimer(TIMER_TETRIS, 100, NULL);
			break;
		case 9:
			pView->SetTimer(TIMER_TETRIS, 50, NULL);
			break;

		default:
			pView->SetTimer(TIMER_TETRIS, 1700, NULL);
			break;

	}

	ME->FG.Figure = ME->FG.NextFigure = -1;

	pView->CreateFigure();
	MySocket->Sendmapstate();

	pView->SetTimer(TIMER_SENDMAPSTATE , SENDTIME , NULL);
	
	int bgm = rand()%BGM_NUM;
	if(bgm){
		PlaySound(NULL, AfxGetInstanceHandle(),  NULL);
		switch(bgm){

			case 0:
				
				PlaySound( MAKEINTERSOURCE(_LOGINSKA), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
				break;
			case 1:

				PlaySound( MAKEINTERSOURCE(_BRADINSKY), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
				break;
			case 2:

				PlaySound( MAKEINTERSOURCE(_BRADINSKY), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
				break;
			case 3:

				PlaySound( MAKEINTERSOURCE(_TROIKA), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
				break;
			case 4:

				PlaySound( MAKEINTERSOURCE(_KALINKA), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
				break;
		}
	}

	pView->VirtualDraw();
}

void CMyDoc::Server_ProceeStart(){

	MySocket->Broadcast(NULL, START_SIGNAL);

	POSITION pos = Server_UserList.GetHeadPosition();
	TUser *user = NULL;

	while(pos != NULL){

		user = (TUser *)Server_UserList.GetNext(pos);
		if(user == NULL)
			continue;

		user->SetSurvive(true);
		
	}

	Start = true;
	pView->SetTimer( TIMER_NEXTLEVEL, 1000, NULL);
	pView->Btn_Start->SetWindowTextW( _T("다시시작"));
}

bool CMyDoc::ExitUser(char* name, int len){

	CString str(name,len);
	TUser *user = Client_NameToTUser(str);
	
	if(user ==NULL)
		return false;
	
	Client_UserList.RemoveAt(Client_UserList.Find(user));
	for(int i=0 ; Client_EnterUsers.GetCount() ; i++){
		if( Client_EnterUsers[i].Compare( str)==0){
			Client_EnterUsers.RemoveAt(i);
			break;
		}
	}

	POSITION pos = Client_UserList.GetHeadPosition();
	user = NULL;

	while(pos != NULL){

		user = (TUser *)Client_UserList.GetNext(pos);
		if(user != NULL){
			continue;
		}

	}

	pView->Lst_EnterList.ResetContent();
	for(int i=0 ; i < Client_EnterUsers.GetCount() ; i++)
		pView->Lst_EnterList.AddString(  Client_EnterUsers[i]);
	
	
}

//서버에서 클라이언트의 게임종료상태를 넘겨 받음
//한명만 남고 모두 끝난다면 전체 클라이언트에게 END_ENDSIGNAL을 보낸다
void CMyDoc::ProcessDead(ON_NAME on_name){

 	CString str(on_name.name , on_name.namelen);
	TUser *user = NameToTUser(str);

	if(user == NULL)
		return;

	user->SetSurvive(false);

	//죽은 사람이 유저수-1 이면 살아남은 사람이 승리하고 게임을 끝낸다.
	int deadnum=0;
	POSITION live = NULL;
	POSITION pos = this->Server_UserList.GetHeadPosition();
	while(pos != NULL){
		
		user = (TUser *)Server_UserList.GetAt(pos);
		if(user->GetSurvive() == false)
			deadnum++;
		else{
			live = pos;
			
		}
		Server_UserList.GetNext(pos);
	}
	if(deadnum == Server_UserList.GetCount()-1){
		
   		memset( &send_name, 0, sizeof(send_name));

		user = (TUser *)Server_UserList.GetAt(live);
		memcpy( send_name.name, StringToChar(user->GetUserNameW()), strlen( StringToChar(user->GetUserNameW()) ));

		send_name.IsServer = false;
		send_name.msg_idx = END_SIGNAL;
		send_name.namelen = strlen( send_name.name);
		send_name.struct_size = sizeof(send_name) - sizeof(int)*HEADER_NUM;
		MySocket->Broadcast( &send_name, END_SIGNAL);
	}
}

//서버에서 클라이언트로 게임종료를 알림
//on_name승리한 사람 이름이 들어가 있음.
void CMyDoc::Client_ProcessEnd(ON_NAME on_name){
	
	CString name(on_name.name, on_name.namelen);
	CString str= name;
	str+= _T("님이 승리하셨습니다!");
	ChatLog += ( _T("\r\n")+str);
	
	TUser *user = NULL;
	POSITION pos = this->Client_UserList.GetHeadPosition();
	while( pos != NULL){
		user = (TUser *)Client_UserList.GetNext(pos);
		
		if( user->GetUserName().Compare(name) != 0)
			user->SetSurvive(false);
	}
	user = this->Client_NameToTUser(name);
	user->SetSurvive(true);

	if(Open){
		pView->Btn_Ready->EnableWindow(false);
		pView->Btn_Start->EnableWindow(true);
		pView->Btn_Start->SetWindowTextW( _T("다시 시작하기"));
	}
	else if(Enter){
		pView->Btn_Start->EnableWindow(false);
		pView->Btn_Ready->EnableWindow(false);
	}

	pView->KillTimer(TIMER_TETRIS);
	pView->KillTimer(TIMER_SENDMAPSTATE);
	End = true;
	Start = false;
	
	pView->VirtualDraw();
}

void CMyDoc::RestartGame(){

	POSITION pos = Client_UserList.GetHeadPosition();
	TUser* user=NULL;

	while(pos != NULL){
		user = (TUser *)Client_UserList.GetNext(pos);
		user->SetReady(false);
		memset( user->StateBoard , 0 , sizeof(user->StateBoard));
		user->SetSurvive(true);

	}

	ME->SetReady(false);
	ME->SetSurvive(true);
	memset( ME->GameBoard , 0, sizeof(ME->GameBoard));
	memset( ME->FixedBoard , 0 , sizeof(ME->FixedBoard));
	memset( ME->NextFigureBoard, 0 , sizeof(ME->NextFigureBoard));
	Ready = false;
	End = false;
	
	if(Open){
		pView->Btn_Ready->EnableWindow(true);
		pView->Btn_Start->EnableWindow(true);
		pView->Btn_Start->SetWindowTextW( _T("시작하기"));
	}
	else if(Enter){
		pView->Btn_Start->EnableWindow(false);
		pView->Btn_Ready->EnableWindow(true);
	}
}
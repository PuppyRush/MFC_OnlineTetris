// MySocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "MySocket.h"
#include "TUser.h"

// CMySocket

using namespace msg_header;

CMySocket::CMySocket(const IPString ipstring, const size_t port)
	: m_ipString(ipstring), m_port(port)
{
}

CMySocket::~CMySocket()
{
}

bool CMySocket::ConnectToServer()
{
	if (!Connect(CString(m_ipString.GetString()), m_port))
		return false;


}

void CMySocket::OnClose(int nErrorCode){

	if(pDoc==NULL)
		return;

	TUser *user = pDoc->SocketToTUser(this);

	//서버에서 먼저 닫히는경우.
	if(user == NULL){
		this->ShutDown();
		this->Close();
		pDoc->ProcessClose();

		pDoc->Server_EnterUsers.RemoveAll();
			
		POSITION pos = NULL;
		pos = pDoc->Server_UserList.GetHeadPosition();
		while( pos != NULL){
			((TUser *)pDoc->Server_UserList.GetAt(pos))->GetSocket()->ShutDown();
			((TUser *)pDoc->Server_UserList.GetAt(pos))->GetSocket()->Close();
			pDoc->Server_UserList.RemoveAt(pos);

		}

		pDoc->SocketList.RemoveAll();
	
		
		return;
	}

	//클라이언트가 닫기를 시도하면 서버에서 onclose가 수행됨

	CString name = user->GetUserName();
	char chname[ID_LEN];

	int len = WideCharToMultiByte(CP_ACP, 0, name, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, name, -1, chname, len, NULL, NULL);

	//서버에 저장된 접속자이름배열에서 접속을 끊은사람을 지운다.
	for(int i=0 ; i < pDoc->Server_EnterUsers.GetCount() ; i++)
		if(pDoc->Server_EnterUsers[i] == name){
			pDoc->Server_EnterUsers.RemoveAt(i);
		}

	//서버에 저장된 유저리스트에서 접속을 끊은사람을 지운다.
	pDoc->Server_UserList.RemoveAt(pDoc->Server_UserList.Find( user));
	delete user;
	user = NULL;
		
	//서버에 저장된 유저소켓리스트에서 접속을 끊은사람을 지운다.
	pDoc->SocketList.RemoveAt( pDoc->SocketList.Find(this));
	//
	//this->ShutDown();
	//this->Close();


	//접속해 있는 나머지 사람들에게 나갔음을 알린다.
	mSendName msg(Header(EXIT_USER), strlen(chname), chname);

	if(!Broadcast( &msg, EXIT_USER))
		pView->MessageHandler(FAIL_SENDMSG);
	
	auto sendmsg = mSendMessage::GetMessage("님이 도중에 나갔습니다");

	if(!Broadcast( &sendmsg, ON_MESSAGE))
		pView->MessageHandler(FAIL_SENDMSG);

	pView->VirtualDraw();
}


void CMySocket::SelfClose(){

	pDoc->Enter = pDoc->Open = false;

	this->ShutDown();
	this->Close();

}

void CMySocket::OnReceive(int nErrorCode){
	if(pView == NULL || pDoc==NULL)
		return;

	TUser *usertmp = NULL;
	CString str;
	int res=-1; 
 	DWORD PacketLen=0;
	char *Buffer;
 	int msg = 0;
	int header[HEADER_NUM] = {0};

	//클라이언트에서 보낸 패킷의 크기를 얻기 위한 함수
 	this->IOCtl(FIONREAD, &PacketLen);
	Buffer = new char[PacketLen];
	
	Receive( Buffer, PacketLen);
  	memcpy(header, Buffer, sizeof(size_t)*HEADER_NUM);

	////서버가 받을 메세지
	//if( header[0]){
	//	
	//	switch(header[1]){
	//		
	//		//서버를 포함하여 클라이언트가 접속하면 최초 수행되는 메세지
	//		//클라이언트가 접속 후 이름없는 TUser객체 생성하고 동시에 이름을 보낸다
	//		case ON_NAME:
	//			
	//			memset( &on_name, 0, sizeof(on_name));
	//			memcpy(&on_name, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
	//			if(pDoc->Adduser( on_name.name, on_name.namelen, this))
	//				if(!Broadcast( NULL, ADD_USERS))
	//					pView->MessageHandler(FAIL_SENDMSG);
	//					
	//			break;
	//		 		
	//		case SEND_MESSAGE:
	//			memset(&on_msg, 0 , sizeof(on_msg));
	//			memcpy(&on_msg, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
	//			if(!Broadcast( &on_msg, ON_MESSAGE))
	//				pView->MessageHandler(FAIL_SENDMSG);
	//
	//			break;
	//
	//		case PER_READY:
	//			memset(&on_ready, 0 , sizeof(on_ready));
	//			memcpy(&on_ready, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
	//			if(!ProcessReady(on_ready))
	//				pView->MessageHandler(-1);
	//			if(!Broadcast( NULL, ON_READY))
	//				pView->MessageHandler(FAIL_SENDMSG);
	//
	//			break;
	//
	//		case BC_MAPSTATE:
	//			memset(&on_map, 0 , sizeof(on_map));
	//			memcpy(&on_map, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
	//			Broadcast( &on_map, ON_MAPSTATE);
	//			break;
	//
	//		case BC_DEAD:
	//			memset(&on_name, 0 , sizeof(on_name));
 	//			memcpy(&on_name, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
	//			pDoc->ProcessDead(on_name);
	//			break;
	//		case BC_ADDLINE:
	//			memset(&on_line, 0 , sizeof(on_line));
 	//			memcpy(&on_line, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
	//			Broadcast( &on_line, ON_ADDLINE);
	//			break;
	//		case BC_RESTART:
	//			Broadcast( NULL, RESTART_SIGNAL);
	//			break;
	//	}
	//
	//}
	////클라이언트가 받을 메세지(서버도 하나의 클라이언트로 정의)
	//else{

	switch(header[0]){

		case PER_NAME:
		{
			auto msg = mSendMessage::GetMessage(pDoc->chName);
			Send((char *)&msg, sizeof(msg));
		}
		break;
					  
		case ON_MESSAGE:
		{
			mOnMessage msg;
			memcpy(&msg, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
			pDoc->AddChat(msg.msg, msg.msglen);
		}
		break;

		case ADD_USERS:
		{
			mOnNames names;
			memcpy(&names, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
			pDoc->SetEnterUsers(names);
			pDoc->SetOrder();
		}
		break;
		
		case ON_READY:
		{
			mOnReadies readies;
			memcpy(&readies, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
			pDoc->SetReady(readies);
		}
		break;

		case EXIT_USER:
		{
			mOnName name;
			memcpy(&name, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
			pDoc->ExitUser(name.name, name.namelen);
		}
		break;

		case FAIL_ENTER:
		{
			mOnPermit permit;
			memcpy(&permit, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
			pView->MessageHandler(permit.res);
			SelfClose();
		}
		break;

		case START_SIGNAL:
		{
			mOnStartsignal sig;
			memcpy(&sig, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
			pDoc->Client_ProcessStart(sig);
		}
		break;

		case END_SIGNAL:
		{
			mOnName name;
			memcpy(&name, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
			pDoc->Client_ProcessEnd(name);
		}
		break;

		case ON_MAPSTATE:
		{
			mOnMapstate mapstate;
			memcpy(&mapstate, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
			pView->ProcessMapState(&mapstate);
		}
		break;

		case ON_ADDLINE:
		{
			mOnAddline addline;
			memcpy(&addline, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
			pView->AddLine(addline.linenum);
		}
		break;

		case RESTART_SIGNAL:
		{
			pDoc->RestartGame();
		}
		break;
	}

}

bool CMySocket::Broadcast(void* strc, int msgidx){

	//POSITION pos = pDoc->Server_UserList.GetHeadPosition();
	//TUser *user = NULL;
	//if(pos == NULL){
	//	return false;
	//}
	//
	//switch(msgidx){
	//
	//	case ON_MESSAGE:{
	//		mOnMessage *tmp = (mOnMessage *)strc;
	//		mSendMessage msg;
	//		memset(&msg , 0, sizeof(msg));
	//		memcpy(msg.msg,  tmp->msg, tmp->msglen);
	//		msg.IsServer = false;
	//		msg.msglen = tmp->msglen;
	//		msg.msg_idx = msgidx;
	//		msg.struct_size = sizeof(msg) - sizeof(int)*HEADER_NUM;
	//
	//		while(pos != NULL){
	//			
	//			user = (TUser *)pDoc->Server_UserList.GetNext(pos);
	//			if(user->GetSocket() == NULL)
	//				continue;
	//			if(user->GetSocket()->Send( (char *)&msg, sizeof(msg)) <=0)
	//				return false;
	//	
	//		}
	//		break;
	//	}			
	//	case ADD_USERS:
	//		
	//		memset(&send_names, 0, sizeof(send_names));
	//
	//		for(int i=0 ; i < pDoc->Server_EnterUsers.GetCount() ; i++){
	//
	//			int len = WideCharToMultiByte(CP_ACP, 0, pDoc->Server_EnterUsers[i], -1, NULL, 0, NULL, NULL);
	//			WideCharToMultiByte(CP_ACP, 0, pDoc->Server_EnterUsers[i], -1, send_names.name[i] , len, NULL, NULL);
	//			send_names.namelen[i] = len;
	//
	//		}
	//
	//		send_names.enternum = pDoc->Server_EnterUsers.GetCount();
	//		send_names.IsServer = false;
	//		send_names.msg_idx = msgidx;
	//		send_names.struct_size = sizeof( send_names) - sizeof(int)*HEADER_NUM;
	//
	//		while(pos != NULL){
	//			user = (TUser *)pDoc->Server_UserList.GetNext(pos);
	//			if(user->GetSocket() == NULL)
	//				continue;
	//			if(user->GetSocket()->Send( (char *)&send_names, sizeof(send_names)) <=0)
	//				return false;		
	//		}
	//		break;
	//
	//	case EXIT_USER:{
	//		mSendName *send_name = (mSendName *)strc;
	//		mSendName name;
	//		memset(&name, 0, sizeof(name));
	//		memcpy(name.name, send_name->name, send_name->namelen);
	//		name.namelen = send_name->namelen;
	//		name.IsServer = false;
	//		name.msg_idx = msgidx;
	//		name.struct_size= sizeof(name) - sizeof(int)*HEADER_NUM;
	//		while(pos != NULL){
	//			user = (TUser *)pDoc->Server_UserList.GetNext(pos);
	//			if(user->GetSocket() == NULL)
	//				continue;
	//			if(user->GetSocket()->Send( (char *)&name, sizeof(name) ) <=0)
	//				return false;		
	//		}
	//
	//		break;
	//	  }
	//	case ON_READY:
	//
	//		memset(&send_readies, 0, sizeof(send_readies));
	//		for(int i=0 ; i < pDoc->Server_EnterUsers.GetCount() ; i++){
	//			
	//			send_readies.ready[i] = pDoc->NameToTUser(pDoc->Server_EnterUsers[i])->GetReady();
	//
	//			int len = WideCharToMultiByte(CP_ACP, 0, pDoc->Server_EnterUsers[i], -1, NULL, 0, NULL, NULL);
	//			WideCharToMultiByte(CP_ACP, 0, pDoc->Server_EnterUsers[i], -1, send_readies.name[i] , len, NULL, NULL);
	//			send_readies.namelen[i] = len;
	//
	//		}
	//
	//		send_readies.enternum = pDoc->Server_EnterUsers.GetCount();
	//		send_readies.IsServer = false;
	//		send_readies.msg_idx = msgidx;
	//		send_readies.struct_size = sizeof(send_readies) - sizeof(int)*HEADER_NUM;
	//
	//		while(pos != NULL){
	//
	//			user = (TUser *)pDoc->Server_UserList.GetNext(pos);
	//			if(user->GetSocket() == NULL)
	//				continue;
	//			if(user->GetSocket()->Send( (char *)&send_readies, sizeof(send_readies) ) <=0)
	//				return false;
	//	
	//		}
	//
	//		break;
	//
	//	case START_SIGNAL:
	//
	//		memset( &send_start, 0, sizeof(send_start));
	//		send_start.level = pDoc->Level;
	//		send_start.map = pDoc->Map;
	//		send_start.ghost = pDoc->Ghost;
	//		send_start.gravity = pDoc->Gravity;
	//		send_start.IsServer = false;
	//		send_start.msg_idx = msgidx;
	//		send_start.struct_size = sizeof(send_start) - sizeof(int)*HEADER_NUM;
	//
	//		while(pos != NULL){
	//
	//			user = (TUser *)pDoc->Server_UserList.GetNext(pos);
	//			
	//			if(user->GetSocket() == NULL)
	//				continue;
	//			if(user->GetSocket()->Send( (char *)&send_start, sizeof(send_start) ) <=0)
	//				return false;
	//	
	//		}
	//
	//		break;
	//
	//	case ON_MAPSTATE:{
	//		mOnMapstate aa = *((mOnMapstate *)strc);
	//		memset( &send_map, 0, sizeof(send_map));
	//		memcpy( send_map.board , aa.board , sizeof(aa.board));
	//		memcpy( send_map.name , aa.name , aa.namelen);
	//		memcpy( send_map.figure, aa.figure , sizeof(POINT)*FG_FIXEDNUM);
	//		send_map.namelen = aa.namelen;
	//		send_map.IsServer = false;
	//		send_map.msg_idx = ON_MAPSTATE;
	//		send_map.struct_size = sizeof(send_map) - sizeof(int)*HEADER_NUM;
	//
	//
	//		while(pos != NULL){
	//			user = (TUser *)pDoc->Server_UserList.GetNext(pos);				
	//			if(user == NULL || user->GetSocket() == NULL )
	//				continue;
	//			if(user->GetSocket()->Send( (char *)&send_map, sizeof(send_map) ) <=0)
	//				return false;				
	//		}
	//	
	//		break;	
	//	}
	//
	//	case END_SIGNAL:{
	//		mSendName send_name;
	//		memset(&send_name,0,sizeof(send_name));
	//		send_name.IsServer = false;
	//		send_name.msg_idx = msgidx;
	//		memcpy( send_name.name , ((mSendName *)strc)->name , strlen(  ((mSendName *)strc)->name ));
	//		send_name.namelen = strlen (  ((mSendName *)strc)->name  );
	//		send_name.struct_size = sizeof(send_name) - sizeof(int)*HEADER_NUM;
	//		
	//		while(pos != NULL){
	//			user = (TUser *)pDoc->Server_UserList.GetNext(pos);				
	//			if(user == NULL || user->GetSocket() == NULL )
	//				continue;
	//			if(user->GetSocket()->Send( (char *)&send_name, sizeof( send_name)) <=0)
	//				return false;				
	//		}
	//
	//		break;
	//	}
	//
	//	case ON_ADDLINE:{
	//		ON_ADDLINE *on_line = (ON_ADDLINE *)strc;
	//		CString name(on_line->name, on_line->namelen);
	//
	//		mSendAddline addline(Header(ON_ADDLINE),)
	//		memset(&send_per, 0, sizeof(send_per));
	//		send_per.msg_idx = msgidx;
	//		send_per.res = on_line->linenum;
	//		while(pos != NULL){
	//			user = (TUser *)pDoc->Server_UserList.GetNext(pos);				
	//			if(user == NULL || user->GetSocket() == NULL  )
	//				continue;
	//			//자기자신은 줄을 추가하지 않는다.
	//			if(user->GetUserName().Compare(name) == 0)
	//				continue;
	//			if(user->GetSocket()->Send( (char *)&send_per, sizeof( send_per)) <=0)
	//				return false;				
	//		}
	//		break;
	//	}
	//	case RESTART_SIGNAL:
	//		memset(&send_per, 0, sizeof(send_per));
	//		send_per.msg_idx = msgidx;
	//
	//		while(pos != NULL){
	//			user = (TUser *)pDoc->Server_UserList.GetNext(pos);				
	//			if(user == NULL || user->GetSocket() == NULL )
	//				continue;
	//			if(user->GetSocket()->Send( (char *)&send_per, sizeof( send_per)) <=0)
	//				return false;				
	//		}
	//		break;
	//					
	//	/*case ON_MAPSTATES:{
	//		while(pos != NULL){
	//			
	//			user = (TUser *)pDoc->Server_UserList.GetNext(pos);
	//			
	//			if(user->GetSocket() == NULL)
	//				continue;
	//			if(user->GetSocket()->Send( (char *)(mSendMapstates *)strc, sizeof(*(mSendMapstates *)strc) ) <=0)
	//				return false;
	//	
	//		}
	//
	//	}
	//		break;*/
	//}//switch
	//
	//
	return false;

}

bool CMySocket::Sendname(char *name, int namelen){

	mSendName sendname(Header(ON_NAME), namelen, name);

	if(pDoc->m_mySocket->Send( (char *)&sendname, sizeof(sendname))>0)
		return true;
	else 
		return false;
}

bool CMySocket::Sendmapstate(){

	if(pDoc == NULL)
		return false;
	
	auto h = Header(BC_MAPSTATE);
	mSendMapstate mapstate(h, pDoc->namelen, pDoc->chName, pDoc->ME->FixedBoard, pDoc->ME->FG.Figure, pDoc->ME->FG.FgInfo);

	if( Send( (char *)&mapstate, sizeof(mapstate) )>0)
		return true;
	else
		return false;

	return false;
}

bool CMySocket::Sendready(bool ready)
{

	mSendReady sendready(Header(PER_READY), pDoc->namelen, pDoc->chName, pDoc->Ready);

	if(Send( (char *)&sendready, sizeof(sendready)) <=0){
		return false;
	}
}

bool CMySocket::ProcessReady(mOnReady rdy){

	CString name(rdy.fromname, rdy.namelen);
	TUser *user = pDoc->NameToTUser(name);
	if(user == NULL)
		return false;
	
	user->SetReady(rdy.ready);
	return true;
}

bool CMySocket::ProcessMapsate(mOnMapstate on_map){

	//static CStringArray AsyncSend;
	//static mSendMapstates map_state;
	//static int idx=0;
	//
	//TUser *user=NULL;
	//char ch[ID_LEN];
	//memset(ch, 0, ID_LEN);
	//memcpy(ch, on_map.name ,on_map.namelen);
	//CString name(ch, on_map.namelen);
	//
	//int i=0;
	//for(i=0 ; i < AsyncSend.GetCount() ; i++){
	//	if(AsyncSend[i].Compare(name)==0)
	//		break;
	//}
	//if( AsyncSend.GetCount() == i){
	//	AsyncSend.Add(name);
	//	memcpy(map_state.board[idx] , on_map.board, sizeof( on_map.board));
	//	memcpy(map_state.name[idx], on_map.name, on_map.namelen);
	//	map_state.namelen[idx] = on_map.namelen;
	//	idx++;
	//}
	//
	//if( AsyncSend.GetCount() == pDoc->Server_UserList.GetCount()){
	//	map_state.enternum = AsyncSend.GetCount();
	//	map_state.msg_idx = ON_MAPSTATES;
	//	Broadcast( &map_state, ON_MAPSTATES);
	//
	//	idx=0;
	//	memset(&map_state, 0, sizeof(map_state));
	//	AsyncSend.RemoveAll();
	//}
	//
	return false;
}

bool CMySocket::SendDead()
{
	mSendName sendname(Header(BC_DEAD), pDoc->namelen, pDoc->chName);
	
	if(Send( (char *)&sendname, sizeof(sendname)) >0)
		return true;
	return false;
}

bool CMySocket::SendRestart()
{
	mSendPermit permit(Header(BC_RESTART), -1);

	if( Send(&permit, sizeof(permit)) >0 )
		return true;
	else
		return false;

	return false;
}

//자기 제외하고 두줄 추가하기
//isSelf에 따라 자기자신도 더할지 판단
bool CMySocket::SendLine(int num=1, bool isSelf=true){

	char name[ID_LEN];
	memset(name, 0, sizeof(char)*ID_LEN);
	size_t namelen = 0;

	if (!isSelf)
	{
		strcat(name, pDoc->chName);
		namelen = pDoc->namelen;
	}

	mSendAddline addline(Header(BC_ADDLINE), namelen, name, num);

	if(Send( (char *)&addline, sizeof(addline)) >0)
		return true;
	return false;
}
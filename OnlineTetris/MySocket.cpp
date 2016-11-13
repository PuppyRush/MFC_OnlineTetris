// MySocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OnlineTetris.h"
#include "MySocket.h"
#include "TUser.h"

// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket 멤버 함수


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
	CMyDoc::SEND_NAME tmp;
	memset(&tmp, 0 , sizeof(tmp));
	memcpy(tmp.name, chname, strlen(chname));
	tmp.namelen = strlen(chname);

	if(!Broadcast( &tmp, EXIT_USER))
		pView->MessageHandler(FAIL_SENDMSG);
	

	char msg[MSG_LEN] = {0};
	memset(&on_msg, 0, sizeof(on_msg));
	strcat(msg, chname);
	strcat(msg, "님이 도중에 나갔습니다");
	memcpy(on_msg.msg, msg, strlen(msg));
	on_msg.msglen = strlen(msg);
	if(!Broadcast( &on_msg, ON_MESSAGE))
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
  	memcpy(header, Buffer, sizeof(int)*HEADER_NUM);

	//서버가 받을 메세지
	if( header[0]){
		
		switch(header[1]){
			
			//서버를 포함하여 클라이언트가 접속하면 최초 수행되는 메세지
			//클라이언트가 접속 후 이름없는 TUser객체 생성하고 동시에 이름을 보낸다
			case ON_NAME:
				
				memset( &on_name, 0, sizeof(on_name));
				memcpy(&on_name, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
				if(pDoc->Adduser( on_name.name, on_name.namelen, this))
					if(!Broadcast( NULL, ADD_USERS))
						pView->MessageHandler(FAIL_SENDMSG);
						
				break;
			 		
			case SEND_MESSAGE:
				memset(&on_msg, 0 , sizeof(on_msg));
				memcpy(&on_msg, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
				if(!Broadcast( &on_msg, ON_MESSAGE))
					pView->MessageHandler(FAIL_SENDMSG);

				break;

			case PER_READY:
				memset(&on_ready, 0 , sizeof(on_ready));
				memcpy(&on_ready, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
				if(!ProcessReady(on_ready))
					pView->MessageHandler(-1);
				if(!Broadcast( NULL, ON_READY))
					pView->MessageHandler(FAIL_SENDMSG);

				break;

			case BC_MAPSTATE:
				memset(&on_map, 0 , sizeof(on_map));
				memcpy(&on_map, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
				Broadcast( &on_map, ON_MAPSTATE);
				break;

			case BC_DEAD:
				memset(&on_name, 0 , sizeof(on_name));
 				memcpy(&on_name, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
				pDoc->ProcessDead(on_name);
				break;
			case BC_ADDLINE:
				memset(&on_line, 0 , sizeof(on_line));
 				memcpy(&on_line, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
				Broadcast( &on_line, ON_ADDLINE);
				break;
			case BC_RESTART:
				Broadcast( NULL, RESTART_SIGNAL);
				break;
		}

	}
	//클라이언트가 받을 메세지(서버도 하나의 클라이언트로 정의)
	else{

		switch(header[1]){

			case PER_NAME:
				memset( &send_name, 0, sizeof(send_name));
				send_name.IsServer = true;
				send_name.msg_idx = ON_NAME;
				memcpy( send_name.name, pDoc->chName, strlen( pDoc->chName));
				send_name.namelen = strlen( pDoc->chName);
				send_name.struct_size = sizeof( send_name);
				Send( (char *)&send_name, sizeof(send_name));
				break;
					  
			case ON_MESSAGE:
				memset( &on_msg, 0, sizeof(on_msg));
				memcpy(&on_msg, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
				pDoc->AddChat( on_msg.msg, on_msg.msglen);
				break;

			case ADD_USERS:
				ZeroMemory(&on_names, sizeof(on_names));
				memcpy(&on_names, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);		
				pDoc->SetEnterUsers(on_names);
				pDoc->SetOrder();
				break;
				
			case ON_READY:
				memset(&on_readies, 0 , sizeof(on_readies));
				memcpy(&on_readies, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
				pDoc->SetReady( on_readies);
				break;

			case EXIT_USER:
				memset(&on_name, 0, sizeof(on_name));
				memcpy(&on_name, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
				pDoc->ExitUser(on_name.name, on_name.namelen);
				break;
			case FAIL_ENTER:
				memset(&on_per, 0, sizeof(on_per));
				pView->MessageHandler(on_per.res);
				SelfClose();
				break;
			case START_SIGNAL:
				memset(&on_start, 0 , sizeof(on_start));
				memcpy(&on_start, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
				pDoc->Client_ProcessStart( on_start);
				break;
			case END_SIGNAL:
 				memset(&on_name, 0, sizeof(on_name));
 				memcpy(&on_name, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
				pDoc->Client_ProcessEnd(on_name);
				break;
			case ON_MAPSTATE:
				memset(&on_map, 0, sizeof(on_map));
				memcpy(&on_map, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
				pView->ProcessMapState(&on_map);
				break;
			case ON_ADDLINE:
				memset(&on_per, 0, sizeof(on_per));
				memcpy(&on_per, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);	
				pView->AddLine(on_per.res);
				break;
			case RESTART_SIGNAL:
				pDoc->RestartGame();
				break;
		}

	}
}

bool CMySocket::Broadcast(void* strc, int msgidx){

	POSITION pos = pDoc->Server_UserList.GetHeadPosition();
	TUser *user = NULL;
	if(pos == NULL){
		return false;
	}

	switch(msgidx){

		case ON_MESSAGE:{
			CMyDoc::ON_MESSAGE *tmp = (CMyDoc::ON_MESSAGE *)strc;
			CMyDoc::SEND_MESSAGE msg;
			memset(&msg , 0, sizeof(msg));
			memcpy(msg.msg,  tmp->msg, tmp->msglen);
			msg.IsServer = false;
			msg.msglen = tmp->msglen;
			msg.msg_idx = msgidx;
			msg.struct_size = sizeof(msg) - sizeof(int)*HEADER_NUM;

			while(pos != NULL){
				
				user = (TUser *)pDoc->Server_UserList.GetNext(pos);
				if(user->GetSocket() == NULL)
					continue;
				if(user->GetSocket()->Send( (char *)&msg, sizeof(msg)) <=0)
					return false;
		
			}
			break;
		}			
		case ADD_USERS:
			
			memset(&send_names, 0, sizeof(send_names));

			for(int i=0 ; i < pDoc->Server_EnterUsers.GetCount() ; i++){

				int len = WideCharToMultiByte(CP_ACP, 0, pDoc->Server_EnterUsers[i], -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, pDoc->Server_EnterUsers[i], -1, send_names.name[i] , len, NULL, NULL);
				send_names.namelen[i] = len;

			}

			send_names.enternum = pDoc->Server_EnterUsers.GetCount();
			send_names.IsServer = false;
			send_names.msg_idx = msgidx;
			send_names.struct_size = sizeof( send_names) - sizeof(int)*HEADER_NUM;
	
			while(pos != NULL){
				user = (TUser *)pDoc->Server_UserList.GetNext(pos);
				if(user->GetSocket() == NULL)
					continue;
				if(user->GetSocket()->Send( (char *)&send_names, sizeof(send_names)) <=0)
					return false;		
			}
			break;

		case EXIT_USER:{
			CMyDoc::SEND_NAME *send_name = (CMyDoc::SEND_NAME *)strc;
			CMyDoc::SEND_NAME name;
			memset(&name, 0, sizeof(name));
			memcpy(name.name, send_name->name, send_name->namelen);
			name.namelen = send_name->namelen;
			name.IsServer = false;
			name.msg_idx = msgidx;
			name.struct_size= sizeof(name) - sizeof(int)*HEADER_NUM;
			while(pos != NULL){
				user = (TUser *)pDoc->Server_UserList.GetNext(pos);
				if(user->GetSocket() == NULL)
					continue;
				if(user->GetSocket()->Send( (char *)&name, sizeof(name) ) <=0)
					return false;		
			}

			break;
		  }
		case ON_READY:

			memset(&send_readies, 0, sizeof(send_readies));
			for(int i=0 ; i < pDoc->Server_EnterUsers.GetCount() ; i++){
				
				send_readies.ready[i] = pDoc->NameToTUser(pDoc->Server_EnterUsers[i])->GetReady();

				int len = WideCharToMultiByte(CP_ACP, 0, pDoc->Server_EnterUsers[i], -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, pDoc->Server_EnterUsers[i], -1, send_readies.name[i] , len, NULL, NULL);
				send_readies.namelen[i] = len;

			}

			send_readies.enternum = pDoc->Server_EnterUsers.GetCount();
			send_readies.IsServer = false;
			send_readies.msg_idx = msgidx;
			send_readies.struct_size = sizeof(send_readies) - sizeof(int)*HEADER_NUM;

			while(pos != NULL){

				user = (TUser *)pDoc->Server_UserList.GetNext(pos);
				if(user->GetSocket() == NULL)
					continue;
				if(user->GetSocket()->Send( (char *)&send_readies, sizeof(send_readies) ) <=0)
					return false;
		
			}

			break;

		case START_SIGNAL:

			memset( &send_start, 0, sizeof(send_start));
			send_start.level = pDoc->Level;
			send_start.map = pDoc->Map;
			send_start.ghost = pDoc->Ghost;
			send_start.gravity = pDoc->Gravity;
			send_start.IsServer = false;
			send_start.msg_idx = msgidx;
			send_start.struct_size = sizeof(send_start) - sizeof(int)*HEADER_NUM;

			while(pos != NULL){

				user = (TUser *)pDoc->Server_UserList.GetNext(pos);
				
				if(user->GetSocket() == NULL)
					continue;
				if(user->GetSocket()->Send( (char *)&send_start, sizeof(send_start) ) <=0)
					return false;
		
			}

			break;

		case ON_MAPSTATE:{
			CMyDoc::ON_MAPSTATE aa = *((CMyDoc::ON_MAPSTATE *)strc);
			memset( &send_map, 0, sizeof(send_map));
			memcpy( send_map.board , aa.board , sizeof(aa.board));
			memcpy( send_map.name , aa.name , aa.namelen);
			memcpy( send_map.figure, aa.figure , sizeof(POINT)*FG_FIXEDNUM);
			send_map.namelen = aa.namelen;
			send_map.IsServer = false;
			send_map.msg_idx = ON_MAPSTATE;
			send_map.struct_size = sizeof(send_map) - sizeof(int)*HEADER_NUM;


			while(pos != NULL){
				user = (TUser *)pDoc->Server_UserList.GetNext(pos);				
				if(user == NULL || user->GetSocket() == NULL )
					continue;
				if(user->GetSocket()->Send( (char *)&send_map, sizeof(send_map) ) <=0)
					return false;				
			}
		
			break;	
		}

		case END_SIGNAL:{
			CMyDoc::SEND_NAME send_name;
			memset(&send_name,0,sizeof(send_name));
			send_name.IsServer = false;
			send_name.msg_idx = msgidx;
			memcpy( send_name.name , ((CMyDoc::SEND_NAME *)strc)->name , strlen(  ((CMyDoc::SEND_NAME *)strc)->name ));
			send_name.namelen = strlen (  ((CMyDoc::SEND_NAME *)strc)->name  );
			send_name.struct_size = sizeof(send_name) - sizeof(int)*HEADER_NUM;
			
			while(pos != NULL){
				user = (TUser *)pDoc->Server_UserList.GetNext(pos);				
				if(user == NULL || user->GetSocket() == NULL )
					continue;
				if(user->GetSocket()->Send( (char *)&send_name, sizeof( send_name)) <=0)
					return false;				
			}

			break;
		}

		case ON_ADDLINE:{
			CMyDoc::ON_ADDLINE *on_line = (CMyDoc::ON_ADDLINE *)strc;
			CString name(on_line->name, on_line->namelen);
			memset(&send_per, 0, sizeof(send_per));
			send_per.IsServer = false;
			send_per.msg_idx = msgidx;
			send_per.res = on_line->linenum;
			while(pos != NULL){
				user = (TUser *)pDoc->Server_UserList.GetNext(pos);				
				if(user == NULL || user->GetSocket() == NULL  )
					continue;
				//자기자신은 줄을 추가하지 않는다.
				if(user->GetUserName().Compare(name) == 0)
					continue;
				if(user->GetSocket()->Send( (char *)&send_per, sizeof( send_per)) <=0)
					return false;				
			}
			break;
		}
		case RESTART_SIGNAL:
			memset(&send_per, 0, sizeof(send_per));
			send_per.IsServer = false;
			send_per.msg_idx = msgidx;
			

			while(pos != NULL){
				user = (TUser *)pDoc->Server_UserList.GetNext(pos);				
				if(user == NULL || user->GetSocket() == NULL )
					continue;
				if(user->GetSocket()->Send( (char *)&send_per, sizeof( send_per)) <=0)
					return false;				
			}
			break;
						
		/*case ON_MAPSTATES:{
			while(pos != NULL){
				
				user = (TUser *)pDoc->Server_UserList.GetNext(pos);
				
				if(user->GetSocket() == NULL)
					continue;
				if(user->GetSocket()->Send( (char *)(CMyDoc::SEND_MAPSTATES *)strc, sizeof(*(CMyDoc::SEND_MAPSTATES *)strc) ) <=0)
					return false;
		
			}

		}
			break;*/
	}//switch



}

bool CMySocket::Sendname(char *name, int namelen){

	memset( &send_name, 0, sizeof(send_name));
	send_name.IsServer = true;
	send_name.msg_idx = ON_NAME;
	memcpy( send_name.name,name, namelen);
	send_name.namelen = namelen;
	send_name.struct_size = sizeof( send_name);
	if(pDoc->MySocket->Send( (char *)&send_name, sizeof(send_name))>0)
		return true;
	else 
		return false;

}

bool CMySocket::Sendmapstate(){

	if(pDoc == NULL)
		return false;
	

	memset(&send_map, 0, sizeof(send_map));
	memcpy(send_map.board, pDoc->ME->FixedBoard , sizeof(int)*HORNUM*VERNUM );
	memcpy(send_map.name , pDoc->chName , strlen(pDoc->chName));
	memcpy(send_map.figure , pDoc->ME->FG.FgInfo, sizeof(POINT)*FG_FIXEDNUM);
	send_map.kindfigure = pDoc->ME->FG.Figure;
	send_map.namelen = strlen( pDoc->chName);
	send_map.IsServer = true;
	send_map.msg_idx = BC_MAPSTATE;
	send_map.struct_size = sizeof( send_map) - sizeof(int)*HEADER_NUM;

	if( Send( (char *)&send_map , sizeof(send_map) )>0)
		return true;
	else
		return false;

	return false;
}

bool CMySocket::Sendready(){


	memset( &send_ready, 0 ,sizeof(send_ready));
	memcpy( send_ready.fromname, pDoc->chName, strlen(pDoc->chName));
	send_ready.IsServer = true;
	send_ready.ready = pDoc->Ready;
	send_ready.msg_idx = PER_READY;
	send_ready.namelen = strlen( pDoc->chName);
	send_ready.struct_size = sizeof(send_ready) - sizeof(int)*HEADER_NUM;

	
	if(Send( (char *)&send_ready, sizeof(send_ready)) <=0){

		return false;
	}
}

bool CMySocket::ProcessReady(CMyDoc::ON_READY rdy){

	CString name(rdy.fromname, rdy.namelen);
	TUser *user = pDoc->NameToTUser(name);
	if(user == NULL)
		return false;
	
	user->SetReady(rdy.ready);
	return true;
}

bool CMySocket::ProcessMapsate(CMyDoc::ON_MAPSTATE on_map){

	static CStringArray AsyncSend;
	static CMyDoc::SEND_MAPSTATES map_state;
	static int idx=0;

	TUser *user=NULL;
	char ch[ID_LEN];
	memset(ch, 0, ID_LEN);
	memcpy(ch, on_map.name ,on_map.namelen);
	CString name(ch, on_map.namelen);

	int i=0;
	for(i=0 ; i < AsyncSend.GetCount() ; i++){
		if(AsyncSend[i].Compare(name)==0)
			break;
	}
	if( AsyncSend.GetCount() == i){
		AsyncSend.Add(name);
		memcpy(map_state.board[idx] , on_map.board, sizeof( on_map.board));
		memcpy(map_state.name[idx], on_map.name, on_map.namelen);
		map_state.namelen[idx] = on_map.namelen;
		idx++;
	}

	if( AsyncSend.GetCount() == pDoc->Server_UserList.GetCount()){
		map_state.enternum = AsyncSend.GetCount();
		map_state.IsServer = false;
		map_state.msg_idx = ON_MAPSTATES;
		map_state.struct_size = sizeof( map_state) - sizeof(int)*HEADER_NUM;
		Broadcast( &map_state, ON_MAPSTATES);

		idx=0;
		memset(&map_state, 0, sizeof(map_state));
		AsyncSend.RemoveAll();
	}

	return false;
}

bool CMySocket::SendDead(){

	memset(&send_name, 0, sizeof(send_name));
 	send_name.IsServer = true;
	send_name.msg_idx = BC_DEAD;
	memcpy(send_name.name , pDoc->chName , strlen(pDoc->chName));
	send_name.namelen = strlen(pDoc->chName);
	send_name.struct_size = sizeof(send_name) - sizeof(int)*HEADER_NUM;
	
	if(Send( (char *)&send_name, sizeof(send_name)) >0)
		return true;
	return false;


}

bool CMySocket::SendRestart(){

	memset(&send_per, 0, sizeof(send_per));
	send_per.IsServer = true;
	send_per.msg_idx = BC_RESTART;
	
	if( Send(&send_per, sizeof(send_per)) >0 )
		return true;
	else
		return false;
	

	return false;
}

//자기 제외하고 두줄 추가하기
//isSelf에 따라 자기자신도 더할지 판단
bool CMySocket::SendLine(int num=1, bool isSelf=true){

	memset(&send_line, 0, sizeof(send_line));
	if(isSelf)
		memset(send_line.name , 0 , sizeof(send_line));
	else
		memcpy(send_line.name , pDoc->chName , strlen(pDoc->chName));

	send_line.IsServer= true;
	send_line.namelen = strlen ( pDoc->chName);
	send_line.struct_size = sizeof(send_name) - sizeof(int)*HEADER_NUM;
	send_line.msg_idx = BC_ADDLINE;
	send_line.linenum = num;
	if(Send( (char *)&send_line, sizeof(send_line)) >0)
		return true;
	return false;
}
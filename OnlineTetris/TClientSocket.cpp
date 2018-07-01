// MySocket.cpp : 구현 파일입니다.
//

#include "../Commons/TType.h"
#include "../Commons/TSocket.h"

#include "stdafx.h"
#include "OnlineTetris.h"
#include "TClientSocket.h"
#include "TClientUser.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CMySocket

using namespace tetris;

CTClientSocket::CTClientSocket()
	:SocketImpl(AF_INET, SOCK_STREAM, 0, IPString{192,168,0,1}, 5905),
	m_isConnected(false),m_me(TClientUser::GetMe())
{

}

CTClientSocket::CTClientSocket(const int domain, const int type, const int protocol, const IPString ip, const t_port port)
	:SocketImpl(domain, type, protocol, ip, port),
	m_isConnected(false)
{}

CTClientSocket::~CTClientSocket()
{}

//void CClientSocket::OnClose(int nErrorCode)
//{
	//TUser *user = pDoc->SocketToTUser(this);
	//
	////서버에서 먼저 닫히는경우.
	//if(user == NULL){
	//	this->ShutDown();
	//	this->Close();
	//	pDoc->ProcessClose();
	//
	//	pDoc->m_serverEnterUsers.RemoveAll();
	//		
	//	POSITION pos = NULL;
	//	pos = pDoc->Server_UserList.GetHeadPosition();
	//	while( pos != NULL){
	//		((TUser *)pDoc->Server_UserList.GetAt(pos))->GetSocket()->ShutDown();
	//		((TUser *)pDoc->Server_UserList.GetAt(pos))->GetSocket()->Close();
	//		pDoc->Server_UserList.RemoveAt(pos);
	//
	//	}
	//
	//	pDoc->SocketList.RemoveAll();
	//
	//	
	//	return;
	//}
	//
	////클라이언트가 닫기를 시도하면 서버에서 onclose가 수행됨
	//
	//CString name = user->getUserName();
	//char chname[ID_LEN];
	//
	//int len = WideCharToMultiByte(CP_ACP, 0, name, -1, NULL, 0, NULL, NULL);
	//WideCharToMultiByte(CP_ACP, 0, name, -1, chname, len, NULL, NULL);
	//
	////서버에 저장된 접속자이름배열에서 접속을 끊은사람을 지운다.
	//for(int i=0 ; i < pDoc->m_serverEnterUsers.GetCount() ; i++)
	//	if(pDoc->m_serverEnterUsers[i] == name){
	//		pDoc->m_serverEnterUsers.RemoveAt(i);
	//	}
	//
	////서버에 저장된 유저리스트에서 접속을 끊은사람을 지운다.
	//pDoc->Server_UserList.RemoveAt(pDoc->Server_UserList.Find( user));
	//delete user;
	//user = NULL;
	//	
	////서버에 저장된 유저소켓리스트에서 접속을 끊은사람을 지운다.
	//pDoc->SocketList.RemoveAt( pDoc->SocketList.Find(this));
	////
	////this->ShutDown();
	////this->Close();
	//
	//
	////접속해 있는 나머지 사람들에게 나갔음을 알린다.
	//mSendName msg(Header(EXIT_USER), strlen(chname), chname);
	//
	//if(!Broadcast( &msg, EXIT_USER))
	//	m_view->MessageHandler(FAIL_SENDMSG);
	//
	//auto sendmsg = mSendMessage::GetMessage("님이 도중에 나갔습니다");
	//
	//if(!Broadcast( &sendmsg, ON_MESSAGE))
	//	m_view->MessageHandler(FAIL_SENDMSG);

	//m_view->VirtualDraw();
//}


void CTClientSocket::SelfClose()
{

	m_isConnected = false;
	close();
}

void CTClientSocket::switchingMessage(const msgElement &msg)
{
	/*switch(msgidx)
	{

	case PER_NAME:
	{
		auto msg = mSendMessage::GetMessage(pDoc->m_name.c_str());
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
		pDoc->ExitUser(string(name.name));
	}
	break;

	case FAIL_ENTER:
	{
		mOnPermit permit;
		memcpy(&permit, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
		m_view->MessageHandler(permit.res);
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
		m_view->ProcessMapState(&mapstate);
	}
	break;

	case ON_ADDLINE:
	{
		mOnAddline addline;
		memcpy(&addline, &Buffer[sizeof(int)*HEADER_NUM / sizeof(char)], header[2]);
		m_view->AddLine(addline.linenum);
	}
	break;

	case RESTART_SIGNAL:
	{
		pDoc->RestartGame();
	}

	default:
		;

	break;
	}*/

}

void CTClientSocket::Broadcast(void* strc, int msgidx)
{

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
	//		for(int i=0 ; i < pDoc->m_serverEnterUsers.GetCount() ; i++){
	//
	//			int len = WideCharToMultiByte(CP_ACP, 0, pDoc->m_serverEnterUsers[i], -1, NULL, 0, NULL, NULL);
	//			WideCharToMultiByte(CP_ACP, 0, pDoc->m_serverEnterUsers[i], -1, send_names.name[i] , len, NULL, NULL);
	//			send_names.namelen[i] = len;
	//
	//		}
	//
	//		send_names.enternum = pDoc->m_serverEnterUsers.GetCount();
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
	//		for(int i=0 ; i < pDoc->m_serverEnterUsers.GetCount() ; i++){
	//			
	//			send_readies.ready[i] = pDoc->NameToTUser(pDoc->m_serverEnterUsers[i])->GetReady();
	//
	//			int len = WideCharToMultiByte(CP_ACP, 0, pDoc->m_serverEnterUsers[i], -1, NULL, 0, NULL, NULL);
	//			WideCharToMultiByte(CP_ACP, 0, pDoc->m_serverEnterUsers[i], -1, send_readies.name[i] , len, NULL, NULL);
	//			send_readies.namelen[i] = len;
	//
	//		}
	//
	//		send_readies.enternum = pDoc->m_serverEnterUsers.GetCount();
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
	//		send_start.level = pDoc->m_level;
	//		send_start.map = pDoc->m_map;
	//		send_start.ghost = pDoc->m_ghost;
	//		send_start.gravity = pDoc->m_gravity;
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
	//			if(user->getUserName().Compare(name) == 0)
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

}

void CTClientSocket::Sendname(const char *name, int namelen)
{
	const auto header = Header(Priority::Normal, toUType(SERVER_MSG::ON_NAME));
	mSendName sendname(header , namelen, name);
	pushMessage(&sendname);
}

void CTClientSocket::Sendmapstate()
{
	auto header = Header(Priority::High, toUType(SERVER_MSG::BC_MAPSTATE));
	mSendMapstate mapstate(header, m_me->getUserName().size() , m_me->getUserName().c_str() , m_me->FixedBoard, m_me->FG.Figure, m_me->FG.FgInfo);

	pushMessage(&mapstate);
}

void CTClientSocket::Sendready(bool ready)
{
	const auto header = Header(Priority::High, toUType(SERVER_MSG::PER_READY));
	mSendReady sendready(header, m_me->getUserName().size() , m_me->getUserName().c_str(), m_me->getReady());
	pushMessage(&sendready);
}

void CTClientSocket::ProcessReady(mOnReady rdy)
{
	//const auto name = string(rdy.fromname);
	//auto user = pDoc->NameToTUser(name);
	//if(user == NULL)
	//	return false;
	//
	//user->SetReady(rdy.ready);
}

void CTClientSocket::ProcessMapsate(mOnMapstate on_map)
{

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

}

void CTClientSocket::SendDead()
{
	const auto header = Header(Priority::High, toUType(SERVER_MSG::BC_DEAD));
	const mSendName sendname(header, m_me->getUserName().size(), m_me->getUserName().c_str());
	pushMessage(&sendname);
}

void CTClientSocket::SendRestart()
{
	const auto header = Header(Priority::Normal, toUType(SERVER_MSG::BC_RESTART));
	mSendPermit permit(header, -1);
	pushMessage(&permit);
}

//자기 제외하고 두줄 추가하기
//isSelf에 따라 자기자신도 더할지 판단
void CTClientSocket::SendLine(int num = 1, bool isSelf = true)
{
	if(!isSelf)
	{
		const auto header = Header(Priority::High, toUType(SERVER_MSG::BC_ADDLINE));
		const auto name = m_me->getUserName();
		mSendAddline addline(header, name.size(), name.c_str(), num);
		pushMessage(&addline);
	}
}
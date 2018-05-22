
// MyDoc.h : CMyDoc 클래스의 인터페이스

#pragma once

#include <memory>
#include <list>
#include <deque>
#include <map>
#include "TetrisUserClient.h"
#include "../Commons/MessageHeader.h"
#include "ServerSocket.h"

using namespace msg_header;

class CMyListen;
class CClientSocket;
class CMyView;

class CMyDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMyDoc();
	DECLARE_DYNCREATE(CMyDoc)

public:


//////////////////////////////////////////////////////////////////////////////


public:
	
	bool Open,Enter;	//이 프로그램이 서버이면 open을 클라이언트면 enter를 true시킨다.
	bool Start;			//모든 접속자가 ready를 누르면 서버가 시작할 수 있다.
	bool Ready;			//클라이언트의 레디 상태
	bool End;			//게임이 끝나면 End로
	bool Ghost;			//낙하예상지점 옵션
	bool Bgm;
	bool Gravity;		//중력모드
	CClientSocket *m_mySocket;
	CMyView *pView;

	std::list<string> Client_EnterUsers;
	std::list<string> Server_EnterUsers;		//접속자의 이름을 위한 변수

	string ServerIp;
	string ChatLog;
	
	std::map<string, SHR_USRC > Client_UserList;
	//std::map<string,CMySocket> SocketList;
	TetrisUser *ME;

	string Name;

	int Map;
	int Level;
	
	int LineRemain;

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMyDoc();

	SHR_USRC Client_NameToTUser(string name);
	void CreateRoot();
	string GetServerIP();
	void AddChat(const char *msg,const int msglen);
	void SetEnterUsers(mOnNames names);
	void SetReady(mOnReadies rdy);
	void SetOrder();
	bool ExitUser(const string name);
	bool ExistUser(string name);
	void ProcessEnter(string );
	void ProcessClose();
	void Client_ProcessEnd(mOnName on_name);
	void ProcessDead(mOnName on_name);
	void Client_ProcessStart(mOnStartsignal on_start);
	void RestartGame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const string& value);
#endif // SHARED_HANDLERS
};

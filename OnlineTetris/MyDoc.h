
// MyDoc.h : CMyDoc 클래스의 인터페이스
//b

#pragma once

#include <memory>

#include "TUser.h"
#include "MessageHeader.h"
#include "DefineInfo.h"
#include "ServerSocket.h"

using namespace msg_header;

class CMyListen;
class CMySocket;
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
	CMySocket *m_mySocket;
	CMyView *pView;

	//mSendPermit per;
	//SEND_STARTSIGNAL send_start;
	//mSendMESSAGE send_msg;
	//SEND_NAME send_name;

	CStringArray Server_EnterUsers;		//접속자의 이름을 위한 변수
	CStringArray Client_EnterUsers;

	CString ServerIp;
	CString ChatLog;
	CPtrList Server_UserList;			//TUser의 객체가 들어감
	
	CPtrList Client_UserList;
	CPtrList SocketList;
	TUser *ME;

	CString Name;
	char chName[ID_LEN];

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

	char *StringToChar(const CString &str);
	CString CharToString(const char *ch, int len);
	CMySocket *NameToSocket(CString name);
	TUser *SocketToTUser(CMySocket *);
	TUser *NameToTUser(CString name);
	TUser *Client_NameToTUser(CString name);
	void CreateRoot();
	CString GetServerIP();
	void AddChat(char *msg, int msglen);
	bool Adduser(char *name, int namelen, CMySocket *soc);
	void SetEnterUsers(ON_NAMES names);
	void SetReady(ON_READIES rdy);
	void SetOrder();
	bool ExitUser(char *name, int namelen);
	bool ExistUser(CString name);
	void ProcessEnter(CString );
	void ProcessClose();
	void Client_ProcessEnd(m_OnName on_name);
	void ProcessDead(m_OnName on_name);
	void Client_ProcessStart(ON_STARTSIGNAL on_start);
	void Server_ProceeStart();
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
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

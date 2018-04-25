
// MyDoc.h : CMyDoc 클래스의 인터페이스
//b

#pragma once

#include <memory>

#include "TUser.h"
#include "DefineInfo.h"
#include "ServerSocket.h"

class CMyListen;
class CMySocket;
class CMyView;

class CMyDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMyDoc();
	DECLARE_DYNCREATE(CMyDoc)

public:
///////////////////////////////////////////////////////////////////////////////
//msg_idx//클라이언트 혹은 서버가 받을 메세지
//IsServer//메세지를 받을 주체가 서버인지 클라이언트 인지?

//메세지를 보낼 구조체
typedef struct SEND_PERMIT{
	bool IsServer;
	int msg_idx;
	int res;
};

typedef struct SEND_NAME{
	bool IsServer;
	int msg_idx;
	int struct_size;
	int namelen;
	char name[ID_LEN];
};

typedef struct SEND_NAMES{
	bool IsServer;
	int msg_idx;
	int struct_size;
	int enternum;
	int namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
};

typedef struct SEND_MESSAGE{
	bool IsServer;
	int msg_idx;
	int struct_size;
	int msglen;
	char msg[MSG_LEN];
};

typedef struct SEND_READY{
	bool IsServer;
	int msg_idx;
	int struct_size;
	int namelen;
	char fromname[ID_LEN];
	bool ready;
};

typedef struct SEND_READIES{
	bool IsServer;
	int msg_idx;
	int struct_size;
	bool ready[MAX_ENTER];
	int enternum;
	int namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
};

typedef struct SEND_STARTSIGNAL{
	bool IsServer;
	int msg_idx;
	int struct_size;
	int map;
	int level;
	bool ghost;
	bool gravity;
};



typedef struct SEND_MAPSTATES{
	bool IsServer;
	int msg_idx;
	int struct_size;
	int enternum;
	int namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
	int board[MAX_ENTER][VERNUM][HORNUM];
};

typedef struct SEND_MAPSTATE{
	bool IsServer;
	int msg_idx;
	int struct_size;
	int namelen;
	char name[ID_LEN];
	int board[VERNUM][HORNUM];
	int kindfigure;
	POINT figure[FG_FIXEDNUM];
};


typedef struct SEND_ADDLINE{
	bool IsServer;
	int msg_idx;
	int struct_size;
	int namelen;
	char name[ID_LEN];
	int linenum;
};

////////////////////////////////////////////////////////////////////////////////

typedef struct ON_PERMIT{

	int res;
};

typedef struct ON_NAME{
	int namelen;
	char name[ID_LEN];

};

typedef struct ON_NAMES{
	int enternum;
	int namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
};


typedef struct ON_MESSAGE{

	int msglen;
	char msg[MSG_LEN];
};

typedef struct ON_READY{
	int namelen;
	char fromname[ID_LEN];
	bool ready;
};


typedef struct ON_READIES{
	bool ready[MAX_ENTER];
	int enternum;
	int namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
};

typedef struct ON_STARTSIGNAL{
	int map;
	int level;
	bool ghost;
	bool gravity;
};


typedef struct ON_MAPSTATE{
	int namelen;
	char name[ID_LEN];
	int board[VERNUM][HORNUM];
	int kindfigure;
	POINT figure[FG_FIXEDNUM];
};

typedef struct ON_MAPSTATES{
	int enternum;
	int namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
	int board[MAX_ENTER][VERNUM][HORNUM];
};

typedef struct ON_ADDLINE{

	int namelen;
	char name[ID_LEN];
	int linenum;
};


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

	SEND_PERMIT per;
	SEND_STARTSIGNAL send_start;
	SEND_MESSAGE send_msg;
	SEND_NAME send_name;

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
	void SetEnterUsers(CMyDoc::ON_NAMES names);
	void SetReady(CMyDoc::ON_READIES rdy);
	void SetOrder();
	bool ExitUser(char *name, int namelen);
	bool ExistUser(CString name);
	void ProcessEnter(CString );
	void ProcessClose();
	void Client_ProcessEnd(ON_NAME on_name);
	void ProcessDead(ON_NAME on_name);
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

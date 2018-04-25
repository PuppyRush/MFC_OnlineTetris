
// MyDoc.h : CMyDoc Ŭ������ �������̽�
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
protected: // serialization������ ��������ϴ�.
	CMyDoc();
	DECLARE_DYNCREATE(CMyDoc)

public:
///////////////////////////////////////////////////////////////////////////////
//msg_idx//Ŭ���̾�Ʈ Ȥ�� ������ ���� �޼���
//IsServer//�޼����� ���� ��ü�� �������� Ŭ���̾�Ʈ ����?

//�޼����� ���� ����ü
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
	
	bool Open,Enter;	//�� ���α׷��� �����̸� open�� Ŭ���̾�Ʈ�� enter�� true��Ų��.
	bool Start;			//��� �����ڰ� ready�� ������ ������ ������ �� �ִ�.
	bool Ready;			//Ŭ���̾�Ʈ�� ���� ����
	bool End;			//������ ������ End��
	bool Ghost;			//���Ͽ������� �ɼ�
	bool Bgm;
	bool Gravity;		//�߷¸��
	CMySocket *m_mySocket;
	CMyView *pView;

	SEND_PERMIT per;
	SEND_STARTSIGNAL send_start;
	SEND_MESSAGE send_msg;
	SEND_NAME send_name;

	CStringArray Server_EnterUsers;		//�������� �̸��� ���� ����
	CStringArray Client_EnterUsers;

	CString ServerIp;
	CString ChatLog;
	CPtrList Server_UserList;			//TUser�� ��ü�� ��
	
	CPtrList Client_UserList;
	CPtrList SocketList;
	TUser *ME;

	CString Name;
	char chName[ID_LEN];

	int Map;
	int Level;
	
	int LineRemain;

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
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

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

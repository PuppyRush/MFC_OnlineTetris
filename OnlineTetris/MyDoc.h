
// MyDoc.h : CMyDoc Ŭ������ �������̽�
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
protected: // serialization������ ��������ϴ�.
	CMyDoc();
	DECLARE_DYNCREATE(CMyDoc)

public:


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

	//mSendPermit per;
	//SEND_STARTSIGNAL send_start;
	//mSendMESSAGE send_msg;
	//SEND_NAME send_name;

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

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};


// MyDoc.h : CMyDoc Ŭ������ �������̽�

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
	CClientSocket *m_mySocket;
	CMyView *pView;

	std::list<string> Client_EnterUsers;
	std::list<string> Server_EnterUsers;		//�������� �̸��� ���� ����

	string ServerIp;
	string ChatLog;
	
	std::map<string, SHR_USRC > Client_UserList;
	//std::map<string,CMySocket> SocketList;
	TetrisUser *ME;

	string Name;

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

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const string& value);
#endif // SHARED_HANDLERS
};

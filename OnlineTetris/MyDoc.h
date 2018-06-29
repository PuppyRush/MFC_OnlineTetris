
// MyDoc.h : CMyDoc Ŭ������ �������̽�

#pragma once

#include <memory>
#include <list>
#include <deque>
#include <map>

#include "../Commons/MessageHeader.h"
#include "../Commons/structs.h"
#include "TClientUser.h"
#include "ServerSocket.h"

using namespace tetris;

class CMyListen;
class CTClientSocket;
class CMyView;

class CMyDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMyDoc();
	DECLARE_DYNCREATE(CMyDoc)

public:


//////////////////////////////////////////////////////////////////////////////


public:
	
	bool m_isStart;			//��� �����ڰ� ready�� ������ ������ ������ �� �ִ�.
	bool m_ready;			//Ŭ���̾�Ʈ�� ���� ����
	bool m_end;			//������ ������ m_end��
	bool m_ghost;			//���Ͽ������� �ɼ�
	bool m_bgm;
	bool m_gravity;		//�߷¸��
	CMyView *m_view;

	std::list<string> m_clientEnterUsers;
	std::list<string> m_serverEnterUsers;		//�������� �̸��� ���� ����

	IPString m_serverIp;
	string m_chatLog;
	
	std::map<string, SHR_USRC > m_clientUserList;
	//std::map<string,CMySocket> SocketList;

	string m_name;

	int m_map;
	int m_level;
	
	int m_lineRemain;

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

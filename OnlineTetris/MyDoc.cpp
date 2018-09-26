
// MyDoc.cpp : CMyDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "OnlineTetris.h"
#endif

#include "MyDoc.h"
#include "MyListen.h"
#include "TClientSocket.h"
#include "MyButton.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CMyDoc

IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
END_MESSAGE_MAP()

// CMyDoc ����/�Ҹ�

CMyDoc::CMyDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	srand((unsigned)time(nullptr));
	m_end = m_ready = m_isStart = false;
	m_map = m_level = 1;
	m_bgm = true;
	m_lineRemain = 0;
}

CMyDoc::~CMyDoc()
{}

BOOL CMyDoc::OnNewDocument()
{
	if(!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.


	return TRUE;
}




// CMyDoc serialization

void CMyDoc::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CMyDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CMyDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMyDoc::SetSearchContent(const CString& value)
{
	if(value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if(pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMyDoc ����

#ifdef _DEBUG
void CMyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyDoc ���

//////////////////////���� �Լ�///////////////////////
//���� ip���
string CMyDoc::GetServerIP()
{
	
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD(2, 0);
	if(WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		if(gethostname(name, sizeof(name)) == 0)
		{
			if((hostinfo = gethostbyname(name)) != nullptr)
			{
				string ip(inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list));
				return ip;
			}
		}
		WSACleanup();
	}

	return string();
}

//�����Լ�
//CMySocket* CMyDoc::NameToSocket(string name)
//{
//	TUser *tmp;
//	POSITION pos = Server_UserList.GetHeadPosition();
//	while(pos != nullptr)
//	{
//		tmp = (TUser  *)Server_UserList.GetNext(pos);
//		if((CMySocket *)tmp->GetUserName().compare(name) == 0)
//		{
//			return tmp->GetSocket();
//			break;
//		}
//	}
//
//	return nullptr;
//}
//�����Լ�
//SHR_USR CMyDoc::NameToTUser(string name)
//{
//
//	TUser *tmp;
//	POSITION pos = Server_UserList.GetHeadPosition();
//	while(pos != nullptr)
//	{
//		tmp = (TUser  *)Server_UserList.GetNext(pos);
//		if((CMySocket *)tmp->GetUserName().compare(name) == 0)
//		{
//
//			return tmp;
//			break;
//		}
//	}
//
//	return nullptr;
//}
//
//TUser *CMyDoc::SocketToTUser(CMySocket *soc)
//{
//
//	TUser *tmp;
//	POSITION pos = Server_UserList.GetHeadPosition();
//	while(pos != nullptr)
//	{
//
//		tmp = (TUser  *)Server_UserList.GetNext(pos);
//		if(tmp->GetSocket() == soc)
//		{
//
//			return tmp;
//			break;
//		}
//	}
//
//	return nullptr;
//
//}

bool CMyDoc::ExistUser(string name)
{
	if(m_clientUserList.count(name) == 0)
		return true;
	else
		return false;
}

void CMyDoc::CreateRoot()
{

	//������ �ϳ��� Ŭ���̾�Ʈ�� ����Ͽ� ������ �ϴ� ��� ������ ���� �ϰ����ְ� ó�� �� �� �ְ� �Ѵ�.
	//if(m_mySocket == nullptr)
	//	m_mySocket = new CMySocket();
	//
	//m_mySocket->m_view = m_view;
	//m_mySocket->pDoc = this;
	//m_mySocket->Create();
	//m_mySocket->Connect( m_serverIp, PORTNUM);
	//
	//TUser *tmp = new TUser(m_name);
	//m_clientUserList.AddTail(tmp);
	//m_view->ME = tmp;
	//
	//if(!m_mySocket->Sendname(chName, strlen(chName)))
	//	m_view->MessageHandler(FAIL_SENDMSG);
	//
	//Enter = false;
	//Open = true;
}


//bool CMyDoc::Adduser(const char *name, CMySocket *soc)
//{
//	int num = 0;
//
//	for each(auto userstr in m_serverEnterUsers)
//	{
//		if(userstr.compare(name) == 0)
//		{
//			mSendPermit send_per(Header(FAIL_ENTER), DUP_ID);
//			soc->Send((char *)&send_per, sizeof(send_per));
//			return false;
//		}
//	}
//
//	TUser *usr = SocketToTUser(soc);
//	if(usr != nullptr)
//	{
//		const string strname(name);
//		usr->SetName(strname);
//		m_serverEnterUsers.push_back(strname);
//	}
//	else
//		m_view->MessageHandler(-1);
//
//	return true;
//}


//Ŭ���̾�Ʈ�Լ�

std::shared_ptr<TClientUser> CMyDoc::Client_NameToTUser(string name)
{
	if(m_clientUserList.count(name) > 0)
		return m_clientUserList.at(name);
	else
		return nullptr;
}

void CMyDoc::AddChat(const char *msg, const int msglen)
{
	CString str(msg, msglen);
	m_chatLog.append(string("\r\n")).append(msg);
	m_view->Edt_ChatEdit.SetWindowTextW(CString(m_chatLog.c_str()));
}

//�濡 �����ϸ� �������� �̸����� ����.
//���� �濡 ������ �ִ»������ �����ϱ� ����.
void CMyDoc::SetEnterUsers(mNames names)
{
	bool nothing = true;

	m_clientEnterUsers.clear();
	m_view->Lst_EnterList.ResetContent();

	for(int i = 0; i < names.enternum; i++)
	{
		string name(names.name[i]);

		//Ŭ���̾�Ʈ�� �̹� ������ ������� ������ü�� ������ �ʴ´�.
		//���°��� �ǴܵǸ� ���� ����
		//if(m_clientUserList.count(name) == 0)
		//	m_clientUserList.insert(make_pair(name, TClientUser::MakeShared(name)));
	}

	//ME = Client_NameToTUser(m_name).get();
	//m_view->ME = ME;
	//if(ME == nullptr)
	//	m_view->MessageHandler(FAIL_FINDNAME);
}

void CMyDoc::SetReady(mRadies rdy)
{
	int rdynum = 0;
	for(int i = 0; i < rdy.enternum; i++)
	{
		string name(rdy.name[i]);

		const auto user = Client_NameToTUser(name);
		if(user == nullptr)
		{
			m_view->MessageHandler(USER_MSG::FAIL_FINDNAME);
			continue;
		}
		user->setReady(rdy.ready[i]);

		if(user->getReady())
			rdynum++;
	}

	if( (rdynum == m_clientEnterUsers.size()))
		m_view->Btn_Start->EnableWindow(true);

	m_view->VirtualDraw();
}

void CMyDoc::SetOrder()
{
	size_t i = 0;
	for each(const auto username in m_clientEnterUsers)
	{
		const auto user = Client_NameToTUser(username);
		if(user == nullptr)
		{
			m_view->MessageHandler(USER_MSG::FAIL_FINDNAME);
			continue;
		}
		user->setOrder(i + 1);
		m_view->Lst_EnterList.AddString(CString(username.c_str()));
		i++;
	}

	//Ŭ���̾�Ʈ(��������) �ڽ��� ������ 1�� �����Ѵ�.
	if(Client_NameToTUser(m_name)->getOrder() != 1)
	{
		int idx = Client_NameToTUser(m_name)->getOrder();
		Client_NameToTUser(m_name)->setOrder(1);

		for each(const auto username in m_clientEnterUsers)
		{
			if(Client_NameToTUser(username)->getOrder() == 1)
			{
				Client_NameToTUser(username)->setOrder(idx);
				break;
			}
		}
	}

	m_view->VirtualDraw();

}

void CMyDoc::ProcessEnter(string name)
{
	m_name = name;

	//auto tmp = TClientUser::MakeShared(name);
	//m_clientUserList.insert( make_pair(name, tmp));

	//TClientSocket::get()->Sendname(name.c_str(), name.size());

	m_view->Btn_Start->EnableWindow(false);
}

void CMyDoc::ProcessClose()
{
	m_view->MessageHandler(USER_MSG::CLOSE_SERVER);
}

//������ ���۽�ȣ�� ������ Ŭ����Ʈ���� ������ ���� ó���� �Ѵ�.
void CMyDoc::Client_ProcessStart(mRoomInitInfo on_start)
{
	m_ghost = on_start.ghost;
	m_view->SetMap(on_start.map);
	m_isStart = true;
	switch(on_start.level)
	{
	case 0:
		m_view->SetTimer(TIMER_TETRIS, 1700, nullptr);
		break;
	case 2:
		m_view->SetTimer(TIMER_TETRIS, 1300, nullptr);
		break;
	case 3:
		m_view->SetTimer(TIMER_TETRIS, 1000, nullptr);
		break;
	case 4:
		m_view->SetTimer(TIMER_TETRIS, 800, nullptr);
		break;
	case 5:
		m_view->SetTimer(TIMER_TETRIS, 600, nullptr);
		break;
	case 6:
		m_view->SetTimer(TIMER_TETRIS, 400, nullptr);
		break;
	case 7:
		m_view->SetTimer(TIMER_TETRIS, 200, nullptr);
		break;
	case 8:
		m_view->SetTimer(TIMER_TETRIS, 100, nullptr);
		break;
	case 9:
		m_view->SetTimer(TIMER_TETRIS, 50, nullptr);
		break;

	default:
		m_view->SetTimer(TIMER_TETRIS, 1700, nullptr);
		break;
	}

	auto &FG = TClientUser::get()->FG;
	FG.Figure = FG.NextFigure = -1;

	m_view->CreateFigure();
	TClientSocket::get()->Sendmapstate();

	m_view->SetTimer(TIMER_SENDMAPSTATE, SENDTIME, nullptr);

	int bgm = rand() % BGM_NUM;
	if(bgm)
	{
		PlaySound(nullptr, AfxGetInstanceHandle(), NULL);
		switch(bgm)
		{

		case 0:

			PlaySound(MAKEINTERSOURCE(_LOGINSKA), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
			break;
		case 1:

			PlaySound(MAKEINTERSOURCE(_BRADINSKY), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
			break;
		case 2:

			PlaySound(MAKEINTERSOURCE(_BRADINSKY), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
			break;
		case 3:

			PlaySound(MAKEINTERSOURCE(_TROIKA), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
			break;
		case 4:

			PlaySound(MAKEINTERSOURCE(_KALINKA), AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP | SND_RESOURCE);
			break;
		}
	}

	m_view->VirtualDraw();
}

//void CMyDoc::Server_ProceeStart()
//{
//
//	m_mySocket->Broadcast(nullptr, START_SIGNAL);
//
//	POSITION pos = Server_UserList.GetHeadPosition();
//	TUser *user = nullptr;
//
//	while(pos != nullptr)
//	{
//
//		user = (TUser *)Server_UserList.GetNext(pos);
//		if(user == nullptr)
//			continue;
//
//		user->setSurvive(true);
//
//	}
//
//	m_isStart = true;
//	m_view->SetTimer(TIMER_NEXTLEVEL, 1000, nullptr);
//	m_view->Btn_Start->SetWindowTextW(_T("�ٽý���"));
//}

bool CMyDoc::ExitUser(const string name)
{
	//TUser *user = Client_NameToTUser(name);
	//if(user == nullptr)
	//	return false;
	//
	//m_clientUserList.RemoveAt(m_clientUserList.Find(user));
	//auto it = m_clientUserList.GetHead();
	//while(it != m_clientUserList.GetTail())
	//{
	//	if(username.compare(name) == 0)
	//	{
	//		m_clientEnterUsers.erase
	//		break;
	//	}
	//
	//}
	//
	//POSITION pos = m_clientUserList.GetHeadPosition();
	//user = nullptr;
	//
	//while(pos != nullptr)
	//{
	//
	//	user = (TUser *)m_clientUserList.GetNext(pos);
	//	if(user != nullptr)
	//	{
	//		continue;
	//	}
	//
	//}
	//
	//m_view->Lst_EnterList.ResetContent();
	//for(int i = 0; i < m_clientEnterUsers.GetCount(); i++)
	//	m_view->Lst_EnterList.AddString(m_clientEnterUsers[i]);
	//
	//
	return true;
}

//�������� Ŭ���̾�Ʈ�� ����������¸� �Ѱ� ����
//�Ѹ� ���� ��� �����ٸ� ��ü Ŭ���̾�Ʈ���� END_ENDSIGNAL�� ������
void CMyDoc::ProcessDead(mName on_name)
{
	const auto name = string(on_name.name);
	//auto user = NameToTUser(name);
	//
	//if(user == nullptr)
	//	return;
	//
	//user->setSurvive(false);

	//���� ����� ������-1 �̸� ��Ƴ��� ����� �¸��ϰ� ������ ������.
	//int deadnum = 0;
	//POSITION live = nullptr;
	//POSITION pos = this->Server_UserList.GetHeadPosition();
	//while(pos != nullptr)
	//{
	//
	//	user = (TUser *)Server_UserList.GetAt(pos);
	//	if(user->GetSurvive() == false)
	//		deadnum++;
	//	else
	//	{
	//		live = pos;
	//
	//	}
	//	Server_UserList.GetNext(pos);
	//}
	//if(deadnum == Server_UserList.GetCount() - 1)
	//{
	//
	//	size_t idlen = strlen(StringToChar(user->GetUserNameW()));
	//	char *name = new char[idlen];
	//
	//	user = (TUser *)Server_UserList.GetAt(live);
	//	memcpy(name, StringToChar(user->GetUserNameW()), idlen);
	//
	//	mSendName sendname(Header(END_SIGNAL), idlen, name);
	//	m_mySocket->Broadcast(&sendname, END_SIGNAL);
	//}
}

//�������� Ŭ���̾�Ʈ�� �������Ḧ �˸�
//on_name�¸��� ��� �̸��� �� ����.
void CMyDoc::Client_ProcessEnd(mName on_name)
{
	string str;
	str.reserve(100);

	str.append(string(on_name.name));
	str.append("���� �¸��ϼ̽��ϴ�!");
	m_chatLog.append( string("\r\n")).append(str);

	for(auto it = m_clientUserList.begin(); it != m_clientUserList.end(); it++)
	{
		const auto username = it->first;
		if(username.compare(username) != 0)
			it->second->setSurvive(false);
		else
			it->second->setSurvive(true);
	}

	//if(Open)
	//{
	//	m_view->Btn_Ready->EnableWindow(false);
	//	m_view->Btn_Start->EnableWindow(true);
	//	m_view->Btn_Start->SetWindowTextW(_T("�ٽ� �����ϱ�"));
	//}
	if(TClientSocket::get()->isConnected())
	{
		m_view->Btn_Start->EnableWindow(false);
		m_view->Btn_Ready->EnableWindow(false);
	}

	m_view->KillTimer(TIMER_TETRIS);
	m_view->KillTimer(TIMER_SENDMAPSTATE);
	m_end = true;
	m_isStart = false;

	m_view->VirtualDraw();
}

void CMyDoc::RestartGame()
{

	for(auto it = m_clientUserList.begin(); it != m_clientUserList.end(); it++)
	{
		it->second->setReady(false);
		it->second->setSurvive(true);
		auto &board = it->second->StateBoard;
		memset(board, 0, sizeof(board));
	}

	auto me = TClientUser::get();

	me->setReady(false);
	me->setSurvive(true);
	memset(me->GameBoard, 0, sizeof(me->GameBoard));
	memset(me->FixedBoard, 0, sizeof(me->FixedBoard));
	memset(me->NextFigureBoard, 0, sizeof(me->NextFigureBoard));
	m_ready = false;
	m_end = false;

	//if(Open)
	//{
	//	m_view->Btn_Ready->EnableWindow(true);
	//	m_view->Btn_Start->EnableWindow(true);
	//	m_view->Btn_Start->SetWindowTextW(_T("�����ϱ�"));
	//}
	if(TClientSocket::get()->isConnected())
	{
		m_view->Btn_Start->EnableWindow(false);
		m_view->Btn_Ready->EnableWindow(true);
	}
}
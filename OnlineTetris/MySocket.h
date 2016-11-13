#pragma once

// CMySocket 명령 대상입니다.

class CMyView;
class CMyDoc;

class CMySocket : public CSocket
{

public:
	CMyView *pView;
	CMyDoc *pDoc;

	CMyDoc::ON_MESSAGE on_msg;
	CMyDoc::SEND_MESSAGE send_msg;
	CMyDoc::SEND_NAME send_name;
	CMyDoc::SEND_NAMES send_names;
	CMyDoc::ON_NAME on_name;
	CMyDoc::ON_NAMES on_names;
	CMyDoc::ON_READY on_ready;
	CMyDoc::SEND_READIES send_readies;
	CMyDoc::ON_READIES on_readies;
	CMyDoc::SEND_PERMIT send_per;
	CMyDoc::ON_PERMIT on_per;
	CMyDoc::ON_STARTSIGNAL on_start;
	CMyDoc::SEND_STARTSIGNAL send_start;
	CMyDoc::ON_MAPSTATE on_map;
	CMyDoc::ON_MAPSTATES on_maps;
	CMyDoc::SEND_MAPSTATE send_map;
	CMyDoc::SEND_READY send_ready;
	CMyDoc::SEND_ADDLINE send_line;
	CMyDoc::ON_ADDLINE on_line;

public:
	CMySocket();
	virtual ~CMySocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	void SelfClose();
	bool Broadcast(void* strc, int msgidx);
	bool Sendname(char* name, int namelen);
	bool Sendmapstate();
	bool Sendready();
	bool SendDead();
	bool SendRestart();
	bool SendLine(int , bool);
	bool ProcessReady(CMyDoc::ON_READY rdy);
	bool ProcessMapsate(CMyDoc::ON_MAPSTATE on_map);
};



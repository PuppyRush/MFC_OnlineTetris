#pragma once

// CMyListen ��� ����Դϴ�.


class CMyDoc;
class CMyView;

class CMyListen : public CAsyncSocket
{

public:

	CMyDoc *pDoc;
	CMyView *pView;
	CMyDoc::SEND_PERMIT per;

public:
	CMyListen();
	CMyListen(CMyView *pV, CMyDoc *pD){ pView = pV; pDoc = pD;}
	virtual ~CMyListen();

	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCodr);
};



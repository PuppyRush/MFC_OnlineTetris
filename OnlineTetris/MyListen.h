#pragma once

// CMyListen ��� ����Դϴ�.


class CMyDoc;
class CMyView;

class CMyListen : public CAsyncSocket
{

public:

public:
	CMyListen();
	virtual ~CMyListen();

	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCodr);
};



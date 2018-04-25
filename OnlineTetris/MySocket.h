#pragma once

// CMySocket 명령 대상입니다.

class CMyView;
class CMyDoc;

class CMySocket : public CSocket
{

public:

	using SHR_SVRSOC = shared_ptr<CServerSocket>;

	typedef struct IPString
	{
	private:
		string ip;
	public:
		explicit IPString(initializer_list<BYTE> fields)
		{
			_ASSERT(fields.size() == 4);
			ip.reserve(16);

			for each(auto b in fields)
			{
				ip.append(std::to_string(static_cast<long>(b)));
				ip.append(".");
			}
		}

		const char* GetString()
		{
			return ip.c_str();
		}
	};

private:

	CMySocket(const string &username, const IPString ipstring, const int port);

public:

	IPString m_ipString;
	int m_port;
	string m_username;

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

	template<class... _Types>
	static shared_ptr<CServerSocket> MakeShared(_Types&&... _Args)
	{
		return make_shared<CServerSocket>(forward<_Types>(_Args)...);
	}


public:
	
	virtual ~CMySocket();
	bool ConnectToServer();
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



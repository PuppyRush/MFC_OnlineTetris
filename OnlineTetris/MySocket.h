#pragma once

// CMySocket 명령 대상입니다.

#include "MessageHeader.h"
#include "DefineInfo.h"

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

public:

	CMySocket(const IPString ipstring, const size_t port);


	IPString m_ipString;
	size_t m_port;
	string m_username;

	CMyView *pView;
	CMyDoc *pDoc;

	//mOnMESSAGE on_msg;
	//mSendMESSAGE send_msg;
	//SEND_NAME send_name;
	//SEND_NAMES send_names;
	//m_OnName on_name;
	//ON_NAMES on_names;
	//m_OnReady on_ready;
	//SEND_READIES send_readies;
	//ON_READIES on_readies;
	//mSendPermit send_per;
	//ON_PERMIT on_per;
	//ON_STARTSIGNAL on_start;
	//SEND_STARTSIGNAL send_start;
	//m_OnMapstate on_map;
	//m_OnMapstates on_maps;
	//SEND_MAPSTATE send_map;
	//SEND_READY send_ready;
	//SEND_ADDLINE send_line;
	//m_OnAddLine on_line;

	template<class... _Types>
	static shared_ptr<CMySocket> GetSocket(_Types&&... _Args)
	{
		static auto mysocket = make_shared<CMySocket>(forward<_Types>(_Args)...);
		return mysocket;
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
	bool ProcessReady(m_OnReady rdy);
	bool ProcessMapsate(m_OnMapstate on_map);
};



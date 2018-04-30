#pragma once

// CMySocket 명령 대상입니다.

#include "MessageHeader.h"

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

	//mOnMessage on_msg;
	//mSendMessage send_msg;
	//SEND_NAME send_name;
	//SEND_NAMES send_names;
	//mOnName on_name;
	//mOnNames on_names;
	//mOnReady on_ready;
	//mSendRadies send_readies;
	//mOnReadies on_readies;
	//mSendPermit send_per;
	//mOnPermit on_per;
	//mOnStartsignal on_start;
	//mSendStartsignal send_start;
	//mOnMapstate on_map;
	//mOnMapstates on_maps;
	//mSendMapstate send_map;
	//mSendReady send_ready;
	//mSendAddline send_line;
	//mOnAddline on_line;

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
	bool Sendready(bool isReady);
	bool SendDead();
	bool SendRestart();
	bool SendLine(int , bool);
	bool ProcessReady(mOnReady rdy);
	bool ProcessMapsate(mOnMapstate on_map);
};



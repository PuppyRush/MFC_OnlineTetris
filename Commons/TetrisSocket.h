#pragma once

#include <functional>
#include <string>
#include <queue>

#include <thread>
#include <mutex>

#include "DefineInfo.h"
#include "Logger.h"
#include "MessageHeader.h"

using namespace std;
using namespace defineinfo;

namespace tetris_socket
{

class TetrisSocket
{

public:

	TetrisSocket() = delete;
	~TetrisSocket();
	explicit TetrisSocket(const int domain, const int type, const int protocol);

	virtual unsigned create(const IPString ip, const unsigned port) = 0;
	virtual unsigned listen() = 0;
	
	static auto getBuffer()
	{
		auto msg = new char[PACKET_LEN]{1};
		assert(!msg);

		return msg;
	}

	template <class T>
	inline	void pushMessage(T *msg)
	{
		assert(PACKET_LEN > sizeof(msg));

		auto dest = getBuffer();
		memcpy(dest, msg, PACKET_LEN);

		m_sendQ.emplace(make_pair(static_cast<const char*>(dest), sizeof(T)));
	}
	inline auto popMessage()
	{
		assert(m_recvQ.empty());

		if(m_recvQ.empty())
		{
			auto msg = m_recvQ.front();
			m_recvQ.pop();
			auto msgptr = shared_ptr<const char>(msg.first,
				[](const char* msg){delete[] msg; });
			return make_pair(msgptr, msg.second);
		}
	}
	inline unsigned popSocket()
	{
		assert(m_acceptedSocketQ.empty());

		if(!m_acceptedSocketQ.empty())
		{
			const unsigned socket = m_acceptedSocketQ.front();
			m_acceptedSocketQ.pop();
		}
	}


	unsigned connect();
	unsigned accept();
	unsigned close();

	void SetIP(const IPString &ip);
	void SetPort(const unsigned port);

protected:

	unsigned m_socket;

	const int m_domain;
	const int m_type;
	const int m_protocol;

	IPString m_ip;
	unsigned m_port;

	std::queue<unsigned> m_acceptedSocketQ;
	bool m_closeSocket;

	//플랫폼마다 사용될 socket의 구현함수들.	
	virtual int _accept() = 0;
	virtual unsigned _connect() = 0;
	virtual unsigned _close(unsigned _socket) = 0;

	virtual const size_t _sendTo(const char *msg,const size_t size) = 0;
	virtual pair<const char*,const size_t> _recvFrom() = 0;
	void _acceptSocket();
	void _send();
	void _recv();

private:
	shared_ptr< std::thread> m_recvThread;
	shared_ptr< std::thread> m_sendThread;
	shared_ptr< std::thread> m_acceptThread;
	

	std::queue<std::pair<const char*, const size_t>> m_recvQ;
	std::queue<std::pair<const char*, const size_t>> m_sendQ;
	
	void _run();
	void _runAcception();
	void _end();

};


}
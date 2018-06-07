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
	virtual ~TetrisSocket();
	explicit TetrisSocket(const int domain, const int type, const int protocol);

	virtual unsigned create(const IPString ip, const unsigned port) = 0;
	virtual int listen(unsigned port, int backlog) = 0;
	
	static auto getBuffer()
	{
		auto msg = new char[PACKET_LEN]{1};
		assert(!msg);

		return msg;
	}

	template <class T>
	inline	void pushMessage(T *msg)
	{
		const size_t len = sizeof(T);
		assert(PACKET_LEN > len);

		char *dest = getBuffer();
		memcpy(dest, msg, PACKET_LEN);

		const auto val = make_pair(static_cast<const char*>(dest), len);
		m_sendQ.emplace(val);
	}
	inline auto popMessage()
	{
		while(true)
		{
			if(m_recvQ.empty())
			{
				auto msg = m_recvQ.front();
				m_recvQ.pop();
				auto msgptr = shared_ptr<const char>(msg.first,
					[](const char* msg){delete[] msg; });
				return make_pair(msgptr, msg.second);
			}
		}
	}
	inline unsigned popSocket()
	{
		while(true)
		{
			if(!m_acceptedSocketQ.empty())
			{
				const unsigned socket = m_acceptedSocketQ.front();
				m_acceptedSocketQ.pop();
				return socket;
			}
		}
	}

	unsigned connect();
	int accept();
	void readnwrite();
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

	//�÷������� ���� socket�� �����Լ���.



	virtual int _accept() = 0;
	virtual unsigned _connect() = 0;
	virtual unsigned _close(const unsigned _socket) = 0;

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

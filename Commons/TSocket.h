#pragma once

#include <functional>
#include <string>
#include <queue>
#include <cstdint>
#include <thread>
#include <mutex>
#include <limits>

#include "DefineInfo.h"
#include "Logger.h"
#include "MessageHeader.h"
#include "TType.h"

#undef min
#undef max

using namespace std;

namespace tetris
{

enum class eElementvalue : std::uint8_t
{
	priority = 0,
	message = 1,
	size = 2
};

struct msgHelper
{
	static constexpr msgElement getMsgElement(const t_priority prio, const char* msg, const size_t size)
	{
		return make_tuple(prio, msg, size);
	}

	static constexpr auto getPriorty(const msgElement &msg)
	{
		return get<toUType(eElementvalue::priority)>(msg);
	}

	static constexpr auto getMessage(const msgElement &msg)
	{
		return get<toUType(eElementvalue::message)>(msg);
	}
	
	static constexpr auto getSize(const msgElement &msg)
	{
		return get<toUType(eElementvalue::size)>(msg);
	}
};

struct msgComp
{
	bool operator()(msgElement &lhs, msgElement &rhs)
	{
		return msgHelper::getPriorty(lhs) > msgHelper::getPriorty(rhs);
	}
};


class TetrisSocket
{
public:
	virtual ~TetrisSocket();

	virtual unsigned create(IPString ip, t_port port) = 0;
	virtual int listen(unsigned port, int backlog) = 0;
	virtual void switchingMessage(const msgElement &msg) = 0;

	static char* getBuffer()
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

		t_priority priority = std::numeric_limits<t_priority>::max();
		memcpy(&priority, msg, sizeof(t_priority));

		const auto val = make_tuple(priority, static_cast<const char*>(dest), len);
		m_sendQ->emplace(val);
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

	void SetIP(IPString &ip);
	void SetPort(t_port port);

protected:
	t_socket m_socket;

	const int m_domain;
	const int m_type;
	const int m_protocol;
	IPString m_ip;
	t_port m_port;

	std::queue<unsigned> m_acceptedSocketQ;
	bool m_closeSocket;

	TetrisSocket() = delete;
	explicit TetrisSocket(const int domain, const int type, const int protocol, const IPString ip, const t_port port);

	virtual int _accept() = 0;
	virtual unsigned _connect() = 0;
	virtual unsigned _close(const unsigned _socket) = 0;

	virtual const size_t _sendTo(const char *msg,const size_t size) = 0;
	virtual msgElement _recvFrom() = 0;
	void _acceptSocket();
	void _send();
	void _recv();


private:
	shared_ptr< std::thread> m_recvThread;
	shared_ptr< std::thread> m_sendThread;
	shared_ptr< std::thread> m_acceptThread;
	shared_ptr< std::thread> m_popThread;

	shared_ptr<std::priority_queue<msgElement,std::vector<msgElement>,msgComp>> m_recvQ;
	shared_ptr<std::priority_queue<msgElement,std::vector<msgElement>,msgComp>> m_sendQ;
	
	void _run();
	void _runAcception();
	void _end();
	void _popMessage();
};


}

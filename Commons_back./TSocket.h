#pragma once

#include <functional>
#include <string>
#include <queue>
#include <cstdint>
#include <thread>
#include <mutex>
#include <limits>
#include <tuple>

#include "DefineInfo.h"
#include "Logger.h"
#include "MessageHeader.h"
#include "TType.h"

#undef min;
#undef max;

namespace tetris
{

using namespace std;
using namespace tetris;
using namespace tetris_type;

enum class eElementValue : elementEnumBase
{
	priority = 0,
	message = 1,
	size = 2
};

struct msgHelper
{

	static constexpr msgElement getMsgElement(const priorityType prio, const char* msg, const size_t size)
	{
		return make_tuple(prio, msg, size);
	}

	static constexpr auto getPriorty(const msgElement &msg)
	{
		//return std::get<toUType(eElementValue::priority)>(msg);
		return std::get<0>(msg);
	}

	static constexpr auto getMessage(const msgElement &msg)
	{
		//constexpr const elementEnumBase idx = toUType(eElementValue::message);
		return std::get<1>(msg);
	}
	
	static constexpr auto getSize(const msgElement &msg)
	{
		return std::get<2>(msg);
		//return get<toUType(eElementValue::size)>(msg);
	}
};

struct msgComp
{
	bool operator()(const msgElement &lhs, const msgElement &rhs)
	{
		return msgHelper::getPriorty(lhs) > msgHelper::getPriorty(rhs);
	}
};


class TetrisSocket
{
public:

	TetrisSocket() = delete;
	virtual ~TetrisSocket();
	explicit TetrisSocket(const int domain, const int type, const int protocol, const IPString ip, const portType port);

	virtual unsigned create(IPString ip, portType port) = 0;
	virtual int listen(unsigned port, int backlog) = 0;
	virtual void switchingMessage(const msgElement &msg) = 0;

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

		priorityType priority = std::numeric_limits<priorityType>::max();
		memcpy(&priority, msg, sizeof(priorityType));

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
	void SetPort(portType port);

protected:

	unsigned m_socket;

	const int m_domain;
	const int m_type;
	const int m_protocol;
	IPString m_ip;
	portType m_port;

	std::queue<unsigned> m_acceptedSocketQ;
	bool m_closeSocket;

	//�÷������� ���� socket�� �����Լ���.

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

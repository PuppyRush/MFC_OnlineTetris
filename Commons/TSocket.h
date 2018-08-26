#pragma once

#include <functional>
#include <string>
#include <queue>
#include <cstdint>
#include <thread>
#include <mutex>
#include <limits>

//#include <assert.h>

#include "TSocket.h"
#include "TObject.h"
#include "DefineInfo.h"
#include "Logger.h"
#include "MessageHeader.h"
#include "TType.h"
#include "TypeTraits.h"
#include "TSwitchingMessage.h"
#undef min
#undef max

class TetrisSocket : public TMessenger, public TObject
{
public:

	virtual ~TetrisSocket();
	virtual tetris::t_error create(IPString ip, tetris::t_port port) = 0;
	virtual tetris::t_error listen(unsigned port, int backlog) = 0;

	template <class T>
	inline	void pushMessage(T *msg)
	{
		const size_t len = sizeof(T);
		assert(PACKET_LEN > len);

		char *dest = getBuffer();
		memcpy(dest, msg, PACKET_LEN);

		tetris::t_priority priority = msg->priority;

		const auto val = std::make_tuple(priority, static_cast<const char*>(dest), len);
		m_sendQ.emplace(val);
	}

	bool operator!=(const TetrisSocket &socket)
	{
		return this->m_socket != socket.m_socket;
	}

	static char* getBuffer();
	tetris::t_socket popSocket();
	tetris::t_error connect();
	tetris::t_error accept();
	void send();
	const tetris::msgElement recv();
	tetris::t_error close();

	void setIP(IPString &ip);
	void setPort(tetris::t_port port);
	inline const tetris::t_socket getUnique() { return m_socket; }

	struct msgComp
	{
		bool operator()(tetris::msgElement &lhs, tetris::msgElement &rhs)
		{
			return msgHelper::getPriority(lhs) > msgHelper::getPriority(rhs);
		}
	};

protected:
	const int m_domain;
	const int m_type;
	const int m_protocol;
	IPString m_ip;
	tetris::t_port m_port;

	std::queue<tetris::t_socket> m_acceptedSocketQ;
	bool m_closeSocket;


	explicit TetrisSocket(const int domain, const int type, const int protocol, const IPString ip, const tetris::t_port port);
	explicit TetrisSocket(const int domain, const int type, const int protocol, tetris::t_socket socket);

	virtual volatile tetris::t_error _accept() = 0;
	virtual tetris::t_error _connect() = 0;
	virtual tetris::t_error _close(const unsigned _socket) = 0;
	virtual const size_t _sendTo(const char *msg,const size_t size) = 0;
	virtual tetris::msgElement _recvFrom() = 0;

	void _acceptSocket();

	inline void setSocket(tetris::t_socket socket) { m_socket = socket;	}

private:
	TetrisSocket() = delete;

	void _runAcception();
	void _end();

	tetris::t_socket m_socket;
	std::shared_ptr<std::thread> m_acceptThread;
	std::priority_queue<tetris::msgElement, std::vector<tetris::msgElement>, msgComp> m_recvQ;
	std::priority_queue<tetris::msgElement, std::vector<tetris::msgElement>, msgComp> m_sendQ;
	

};

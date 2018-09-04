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
#include "../DefineInfo.h"
#include "../Logger.h"
#include "../TMessage.h"
#include "../TType.h"
#include "../TypeTraits.h"
#include "../TMessenger.h"
#include "../TFunctional.h"
#undef min
#undef max

class TetrisSocket : public TMessenger, public TObject
{
public:

	virtual ~TetrisSocket();
	virtual tetris::t_error create(IPString ip, tetris::t_port port) = 0;
	virtual tetris::t_error listen(unsigned port, int backlog) = 0;



	bool operator!=(const TetrisSocket &socket)
	{
		return this->m_socket != socket.m_socket;
	}

	tetris::t_socket popSocket();
	tetris::t_error connect();
	tetris::t_error accept();
	void send(const tetris::msgElement msg);
	const tetris::msgElement recv();
	tetris::t_error close();

	void setIP(IPString &ip);
	void setPort(tetris::t_port port);
	inline const tetris::t_socket getUnique() { return m_socket; }



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
};

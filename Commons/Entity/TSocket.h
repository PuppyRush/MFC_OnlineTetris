#pragma once

#include <functional>
#include <string>
#include <queue>
#include <cstdint>
#include <thread>
#include <mutex>
#include <limits>
#include <numeric>

#include "TObject.h"
#include "../Logger.h"
#include "../TFunctional.h"

#undef min
#undef max

class TetrisSocket : public TObject
{
public:
	enum class property : tetris::t_socket
	{
		Broadcast = std::numeric_limits<tetris::t_socket>::max(),
		Invalidation = Broadcast-1
	};

	using dist = distinguishType<TetrisSocket>;

	virtual ~TetrisSocket();
	virtual tetris::t_error create(IPString ip, tetris::t_port port) = 0;
	virtual tetris::t_error listen(unsigned port, int backlog) = 0;

	bool operator!=(const TetrisSocket &socket)
	{
		return this->m_socket != socket.m_socket;
	}

	inline const tetris::t_socket getSocket() const noexcept { return m_socket; }
	inline void setIP(const IPString &ip)	 noexcept { m_ip = ip; }
	inline const IPString getIP() const noexcept { m_ip; }
	inline void setPort(tetris::t_port port) noexcept { m_port = port; }
	inline const tetris::t_port  getPort() const noexcept { return m_port; }
	inline void setClose(const bool close) { m_closeSocket = close; }
	inline const bool isClose() const noexcept { return m_closeSocket; }

	tetris::t_error connect();
	tetris::t_error accept();
	void send(const TMessageObject& msg);
	const TMessageObject recv();
	tetris::t_error close();

protected:
	const int m_domain;
	const int m_type;
	const int m_protocol;
	IPString m_ip;
	tetris::t_port m_port;

	bool m_closeSocket;

	explicit TetrisSocket(const int domain, const int type, const int protocol, const IPString ip, const tetris::t_port port);
	explicit TetrisSocket(const int domain, const int type, const int protocol, tetris::t_socket socket);

	virtual volatile tetris::t_socket _accept() = 0;
	virtual tetris::t_error _connect() = 0;
	virtual tetris::t_error _close(const unsigned _socket) = 0;
	virtual const size_t _sendTo(const char *msg, const size_t size) = 0;
	virtual const TMessageObject _recvFrom() = 0;

	inline void setSocket(tetris::t_socket socket) { m_socket = socket; }

private:
	TetrisSocket() = delete;

	void _end();

	tetris::t_socket m_socket;
	std::shared_ptr<std::thread> m_acceptThread;

};

#pragma once

#include <unordered_set>

#include "TType.h"
#include "TSocket.h"

class TSocketThread
{
public:
	~TSocketThread();
	void run();
	void end();
	void add(shared_ptr<TetrisSocket> socket);
	void remove(shared_ptr<TetrisSocket> socket);

private:
	TSocketThread();
	TSocketThread(const shared_ptr<TetrisSocket> socket);
	TSocketThread(const unordered_set<shared_ptr<TetrisSocket>>& sockets);

	void _send();
	void _recv();

	std::unordered_set<shared_ptr<TetrisSocket>> m_sockets;
	bool m_closeSocket;
	shared_ptr<thread> m_recvThread;
	shared_ptr<thread> m_sendThread;
};


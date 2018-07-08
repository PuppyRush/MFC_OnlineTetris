#pragma once

#include <unordered_set>
#include <thread>
#include <mutex>

#include "Uncopyable.h"
#include "TType.h"
#include "TSocket.h"

class TSocketThread : private Uncopyable
{
public:
	~TSocketThread();
	void run();
	const tetris::msgElement pop();
	void end();

private:
	TSocketThread();

	void _send();
	void _recv();

	bool m_continue;
	std::mutex	m_recvMutex;
	shared_ptr<thread> m_recvThread;
	shared_ptr<thread> m_sendThread;
	shared_ptr<thread> m_popThread;
};


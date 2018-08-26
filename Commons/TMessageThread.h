#pragma once

#include <unordered_set>
#include <thread>
#include <mutex>

#include "Uncopyable.h"
#include "TType.h"
#include "TSocket.h"
#include "TObjectContainer.h"
#include "TSwitchingMessage.h"
#include "TUser.h"

class TSocketThread : private Uncopyable
{
public:
	virtual ~TSocketThread();
	void run();
	void end();

	inline static std::shared_ptr<TSocketThread> get()
	{
		static std::shared_ptr<TSocketThread> th = std::shared_ptr<TSocketThread>(new TSocketThread());
		return th;
	}

private:
	TSocketThread();

	void _send() ;
	void _recv() ;
	void _switchingMessage();

	std::queue<tetris::msgElement> m_messageQ;

	bool m_continue;
	std::shared_ptr<std::thread> m_recvThread;
	std::shared_ptr<std::thread> m_sendThread;
	std::shared_ptr<std::thread> m_popThread;
};

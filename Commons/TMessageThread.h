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

class TMessageThread : private Uncopyable
{
public:
	virtual ~TMessageThread();
	void run();
	void end();

	inline static std::shared_ptr<TMessageThread> get()
	{
		static std::shared_ptr<TMessageThread> th = std::shared_ptr<TMessageThread>(new TMessageThread());
		return th;
	}

private:
	TMessageThread();

	void _send() ;
	void _recv() ;
	void _switchingMessage();

	std::queue<tetris::msgElement> m_messageQ;

	bool m_continue;
	std::shared_ptr<std::thread> m_recvThread;
	std::shared_ptr<std::thread> m_sendThread;
	std::shared_ptr<std::thread> m_popThread;
};

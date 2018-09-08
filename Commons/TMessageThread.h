#pragma once

#include <unordered_set>
#include <queue>
#include <thread>
#include <mutex>
#include <functional>

#include "Uncopyable.h"
#include "TType.h"
#include "Entity/TSocket.h"
#include "Entity/TUser.h"
#include "Entity/Room/TIGameRoom.h"
#include "Entity/Room/TIWaitingRoom.h"
#include "TObjectContainer.h"
#include "TMessageObject.h"


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

	std::priority_queue<TMessageObject, std::vector<TMessageObject>, std::greater<TMessageObject> > m_messageQ;

	bool m_continue;
	std::shared_ptr<std::thread> m_recvThread;
	std::shared_ptr<std::thread> m_sendThread;
	std::shared_ptr<std::thread> m_popThread;

	TObjectContainer<TetrisUser> *m_userCon;
	TObjectContainer<TetrisSocket> *m_socketCon;
	TObjectContainer<TIGameRoom> *m_gameroomCon;
	TObjectContainer<TIWaitingRoom> *m_waitingroomCon;

};

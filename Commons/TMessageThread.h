#pragma once

#include <unordered_set>
#include <queue>
#include <thread>
#include <mutex>

#include "Uncopyable.h"
#include "TType.h"
#include "Entity/TSocket.h"
#include "Entity/TUser.h"
#include "Entity/Room/TIGameRoom.h"
#include "Entity/Room/TIWaitingRoom.h"
#include "TObjectContainer.h"
#include "TMessenger.h"

#include <functional>

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

	std::priority_queue<tetris::msgElement, std::vector<tetris::msgElement>, std::greater<tetris::msgElement> > m_messageQ;

	bool m_continue;
	std::shared_ptr<std::thread> m_recvThread;
	std::shared_ptr<std::thread> m_sendThread;
	std::shared_ptr<std::thread> m_popThread;

	TObjectContainer<tetris::t_userUnique, TetrisUser> *m_userCon;
	TObjectContainer<tetris::t_socketUnique , TetrisSocket> *m_socketCon;
	TObjectContainer<tetris::t_roomUnique, TIGameRoom> *m_gameroomCon;
	TObjectContainer<tetris::t_roomUnique, TIWaitingRoom> *m_waitingroomCon;

};

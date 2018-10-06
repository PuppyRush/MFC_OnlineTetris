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

	inline static tetris::t_ptr<TMessageThread> get()
	{
		static tetris::t_ptr<TMessageThread> th = tetris::t_ptr<TMessageThread>(new TMessageThread());
		return th;
	}

private:
	bool m_continue;
	tetris::t_ptr<std::thread> m_recvThread;
	tetris::t_ptr<std::thread> m_sendThread;
	tetris::t_ptr<std::thread> m_popThread;

	tetris::t_ptr<TObjectContainer<TetrisUser>> m_userCon;
	tetris::t_ptr<TObjectContainer<TetrisSocket>> m_socketCon;
	tetris::t_ptr<TObjectContainer<TIGameRoom>> m_gameroomCon;
	tetris::t_ptr<TObjectContainer<TIWaitingRoom>> m_waitingroomCon;

	std::vector<tetris::t_ptr<ITObjectContainer>> m_objcontainerAry;

	TMessageThread();
	void _send() ;
	void _recv() ;
	void _switchingMessage();
};

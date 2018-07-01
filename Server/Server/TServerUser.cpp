/*
 * TetrisUserServer.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <string>
#include <sys/socket.h>

#include "../Room/TWaitingRoom.h"
#include "../../Commons/MessageHeader.h"
#include "TServerUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TServerUser::TServerUser(const tetris::t_userUnique unique)
	:TetrisUser(unique),
	m_sharedPtr(shared_ptr<TServerUser>(new TServerUser()))
{
}

TServerUser::TServerUser(TServerUser* user)
	:TetrisUser(user->getUnique())
{
}

TServerUser::~TServerUser()
{
	// TODO Auto-generated destructor stub
}

const tetris::t_error TServerUser::switchingMessage(const tetris::msgElement &msg)
{

}
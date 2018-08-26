#include "TUser.h"
#include "TSocket.h"

#include <memory.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


TetrisUser::TetrisUser(const tetris::t_userUnique unique)
	:m_unique(unique)
{
}

TetrisUser::TetrisUser()
{}

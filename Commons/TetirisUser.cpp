#include "TetrisUser.h"

#include <memory.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TetrisUser::TetrisUser()
{}

TetrisUser::TetrisUser(const string &name, const IPString &ip, const int idx)
	:Name(name),Ip(ip),isReady(false),Order(idx)
{
	memset(StateBoard, 0, sizeof(StateBoard));
	memset(GameBoard, 0, sizeof(GameBoard));
	memset(FixedBoard, 0, sizeof(FixedBoard));

	GhostFG.end = tPOINT();
}


TetrisUser::TetrisUser(const string &name)
	:isReady(false), isSurvive(true),Name(name)
{
	memset(StateBoard, 0, sizeof(StateBoard));
	memset(GameBoard, 0, sizeof(GameBoard));
	memset(FixedBoard, 0, sizeof(FixedBoard));

	GhostFG.end = tPOINT();
}



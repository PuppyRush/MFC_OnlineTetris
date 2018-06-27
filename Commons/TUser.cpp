#include "TUser.h"

#include <memory.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

TetrisUser::TetrisUser()
{}

TetrisUser::TetrisUser(const string &name, const IPString &ip, const int idx)
	:m_name(name), m_ip(ip), m_isReady(false), m_order(idx)
{
	memset(StateBoard, 0, sizeof(StateBoard));
	memset(GameBoard, 0, sizeof(GameBoard));
	memset(FixedBoard, 0, sizeof(FixedBoard));

	GhostFG.end = tPOINT();
}


TetrisUser::TetrisUser(const string &name)
	:m_isReady(false), m_isSurvive(true), m_name(name)
{
	memset(StateBoard, 0, sizeof(StateBoard));
	memset(GameBoard, 0, sizeof(GameBoard));
	memset(FixedBoard, 0, sizeof(FixedBoard));

	GhostFG.end = tPOINT();
}

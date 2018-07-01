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

TetrisUser::TetrisUser(const tetris::t_userUnique unique)
	:m_isReady(false),
	m_isSurvive(true),
	m_name(string()),
	m_unique(unique)
{
	memset(StateBoard, 0, sizeof(StateBoard));
	memset(GameBoard, 0, sizeof(GameBoard));
	memset(FixedBoard, 0, sizeof(FixedBoard));

	GhostFG.end = tPOINT();
}

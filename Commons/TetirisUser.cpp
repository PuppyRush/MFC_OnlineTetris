#include "TetrisUser.h"

#include <memory.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TetrisUser::TetrisUser(const string &name, const IPString &ip, const int idx)
	:Name(name),Ip(ip),isReady(false),Order(idx)
{

	//int len = WideCharToMultiByte(CP_ACP, 0, Name, -1, NULL, 0, NULL, NULL);
	//WideCharToMultiByte(CP_ACP, 0, Name, -1, chName , len, NULL, NULL);

	memset(StateBoard, 0, sizeof(StateBoard));
	memset(GameBoard, 0, sizeof(GameBoard));
	memset(FixedBoard, 0, sizeof(FixedBoard));

	GhostFG.end = tPOINT();
}


TetrisUser::TetrisUser(const string &name)
	:isReady(false), isSurvive(true),Name(name)
{
	//WideCharToMultiByte(CP_ACP, 0, Name, -1, chName , len, NULL, NULL);
	//int len = WideCharToMultiByte(CP_ACP, 0, Name, -1, NULL, 0, NULL, NULL);

	memset(StateBoard, 0, sizeof(StateBoard));
	memset(GameBoard, 0, sizeof(GameBoard));
	memset(FixedBoard, 0, sizeof(FixedBoard));

	GhostFG.end = tPOINT();
}



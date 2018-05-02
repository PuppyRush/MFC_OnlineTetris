#include "StdAfx.h"
#include "TUser.h"


TUser::TUser(const string &name, const string &ip, CMySocket* soc, const int idx)
{
	Name = name;
	Ip = ip;
	Socket = soc;
	isReady = false;
	Order = idx;

	//int len = WideCharToMultiByte(CP_ACP, 0, Name, -1, NULL, 0, NULL, NULL);
	//WideCharToMultiByte(CP_ACP, 0, Name, -1, chName , len, NULL, NULL);

	memset(StateBoard, 0, sizeof(StateBoard));
	memset(GameBoard, 0, sizeof(GameBoard));
	memset(FixedBoard, 0, sizeof(FixedBoard));

	GhostFG.end = POINT();
}


TUser::~TUser(void)
{}

TUser::TUser(const string &name)
{
	isReady = false;
	isSurvive = true;
	Name = name;

	//WideCharToMultiByte(CP_ACP, 0, Name, -1, chName , len, NULL, NULL);
	//int len = WideCharToMultiByte(CP_ACP, 0, Name, -1, NULL, 0, NULL, NULL);

	memset(StateBoard, 0, sizeof(StateBoard));
	memset(GameBoard, 0, sizeof(GameBoard));
	memset(FixedBoard, 0, sizeof(FixedBoard));

	GhostFG.end = POINT();
}


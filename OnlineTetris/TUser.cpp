#include "StdAfx.h"
#include "TUser.h"

TUser::TUser(void)
{
	Ready = false;
	Survive = true;
	Order = 0;

	GhostFG.end = POINT();
}

TUser::TUser(CString name, CString ip, CMySocket* soc, int idx){
	Name = name; 
	Ip = ip; 
	Socket = soc;
	Ready = false;
	Order = idx;

	int len = WideCharToMultiByte(CP_ACP, 0, Name, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, Name, -1, chName , len, NULL, NULL);

	memset(StateBoard, 0, sizeof(StateBoard));
	memset(GameBoard, 0, sizeof(GameBoard));
	memset(FixedBoard, 0 , sizeof(FixedBoard));

	GhostFG.end = POINT();
}


TUser::~TUser(void)
{
}

TUser::TUser(CString name){ 
	Ready = false;
	Survive = true;
	Name = name;

	int len = WideCharToMultiByte(CP_ACP, 0, Name, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, Name, -1, chName , len, NULL, NULL);

	memset(StateBoard, 0, sizeof(StateBoard));
	memset(GameBoard, 0, sizeof(GameBoard));
	memset(FixedBoard, 0 , sizeof(FixedBoard));

	GhostFG.end = POINT();
}


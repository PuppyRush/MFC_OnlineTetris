#pragma once

class CMySocket;

class TUser
{

private:

	int Order;
	char chName[12];
	CString Name;
	CString Ip;
	
	CMySocket *Socket;

	bool Ready;
	bool Server;
	bool Survive;

	

public:


typedef struct FIGURE{	
	POINT FgInfo[4];		//*************************************DefineInfo.h�� �����Ǿ���� ����
	POINT end;				//���� ���ʾƷ��� ��ǥ�� �����Ѵ�.
	int Figure,NextFigure;
	int Height;
	int Width;
	int dir;
};

	int GameBoard[25][10],FixedBoard[25][10],NextFigureBoard[4][2];
	int StateBoard[25][10];
	FIGURE FG;
	FIGURE GhostFG;

public:

	TUser(void);
	TUser(CString name);
	TUser(CString name, CString ip, CMySocket* soc, int idx);
	~TUser(void);

	CString GetUserName(){ return Name;}
	char *GetUserchName(){ return chName;}
	CMySocket *GetSocket(){ return Socket;}
	bool GetReady(){ return Ready;}
	int GetOrder(){ return Order;}
	bool GetSurvive(){ return Survive;}

	void SetSurvive(bool n){ Survive = n;}
	void SetOrder(int idx){ Order = idx;}
	void SetName(CString name){ Name = name;}
	void SetReady(bool rdy){ Ready = rdy;}
};


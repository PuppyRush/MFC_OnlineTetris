#pragma once

#include "../Commons/structs.h"

#undef GetUserName

class CMySocket;

class TUser
{

private:

	int Order;
	char chName[12];
	string Name;
	string Ip;
	
	CMySocket *Socket;

	bool isReady;
	bool isServer;
	bool isSurvive;

public:

	int GameBoard[25][10], FixedBoard[25][10], NextFigureBoard[4][2];
	int StateBoard[25][10];
	FIGURE FG;
	FIGURE GhostFG;

private:

	TUser(void);

	

public:

	TUser(const string &name);
	TUser(const string &name, const string &ip, CMySocket* soc, const int idx);
	
	~TUser(void);

	bool operator< (const TUser &user)
	{
		return this->Order < user.Order;
	}

	static shared_ptr<TUser> MakeShared(const string &name)
	{
		return make_shared<TUser>(name);
	}

	static shared_ptr<TUser> MakeShared(const string &name, const string &ip, CMySocket* soc, const int idx)
	{
		return make_shared<TUser>(name,ip,soc,idx);
	}

	inline const string GetUserName(){ return Name;}
	inline CMySocket *GetSocket(){ return Socket;}
	inline const bool GetReady(){ return isReady;}
	inline const int GetOrder(){ return Order;}
	inline const bool GetSurvive(){ return isSurvive;}

	inline void SetSurvive(const bool n){ isSurvive = n;}
	inline void SetOrder  (const int idx){ Order = idx;}
	inline void SetName   (const string name){ Name = name;}
	inline void SetReady  (const bool rdy){ isReady = rdy;}
};

using SHR_USR = std::shared_ptr<TUser>;
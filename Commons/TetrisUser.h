#pragma once

#include <memory>
#include "../Commons/structs.h"
#include "TetrisSocket.h"

#undef GetUserName

class TetrisUser : private uncopyable
{

public:

	int GameBoard[25][10], FixedBoard[25][10], NextFigureBoard[4][2];
	int StateBoard[25][10];
	FIGURE FG;
	FIGURE GhostFG;

	inline bool operator< (const TetrisUser &user)
	{
		return this->Order < user.GetOrder();
	}

	inline const string GetUserName() const { return Name;}
	inline const bool GetReady() const { return isReady;}
	inline const int GetOrder() const { return Order;}
	inline const bool GetSurvive() const { return isSurvive;}

	inline void SetSurvive(const bool n) { isSurvive = n;}
	inline void SetOrder  (const int idx){ Order = idx;}
	inline void SetName   (const string name){ Name = name;}
	inline void SetReady  (const bool rdy){ isReady = rdy;}

protected:

	int Order;
	string Name;
	IPString Ip;

	bool isReady;
	bool isServer;
	bool isSurvive;

	TetrisUser(const string &name);
	TetrisUser(const string &name, const IPString &ip, const int idx);

	explicit TetrisUser();
	virtual ~TetrisUser(void){ }

private:

};

using SHR_USR = std::shared_ptr<TetrisUser>;

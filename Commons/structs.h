#pragma once

#include <string>
#include <cassert>

#include <ctime>
#include "TType.h"

#undef POINT



class IPString
{

public:
	IPString()
	{
		IPString({192,168,0,1});
	}

	explicit IPString(std::initializer_list<size_t> fields)
	{
		assert(fields.size() == 4);
		ip.reserve(16);
		for (size_t b : fields)
		{
			ip.append(std::to_string(static_cast<long>(b)));
			ip.append(".");
		}
		ip.pop_back();
	}

	const char* GetString() const
	{
		return ip.c_str();
	}

private:
	std::string ip;
};

typedef struct tPOINT
{
	long x;
	long y;
}tPOINT;


typedef struct FIGURE
{
	tPOINT FgInfo[4];		//*************************************DefineInfo.h�� �����Ǿ���� ����
	tPOINT end;				//���� ���ʾƷ��� ��ǥ�� �����Ѵ�.
	int Figure, NextFigure;
	int Height;
	int Width;
	int dir;
}FIGURE;

typedef struct userInfo
{
	tetris::t_unique userUnique;
	std::string name;

	userInfo() {}
	explicit userInfo(const tetris::t_unique userUnique, const std::string name)
		:userUnique(userUnique),
		name(name)
	{}
}UserInfo;

typedef struct roomInfo
{
	tetris::t_unique unique;
	time_t makeTime;
	size_t roomNumber;
	std::string roomName;
	size_t fullUserCount;
	size_t currentUserCount;

	roomInfo() {}
	explicit roomInfo(const tetris::t_unique unique, const time_t makeTime, const std::string roomName
	,const size_t roomnumber, const size_t fullusercount, const size_t currentusercount)
		:unique(unique), makeTime(makeTime), roomName(roomName)
		, roomNumber(roomnumber), fullUserCount(fullusercount), currentUserCount(currentusercount)
	{}
}RoomInfo;

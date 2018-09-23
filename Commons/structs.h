

#pragma once

#include <string>
#include <cassert>
#include <string.h>
#include <ctime>

#include "TType.h"
#include "DefineInfo.h"
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
	short x;
	short y;
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

#pragma pack(push,1)

typedef struct UserInfo
{
public:
	char name[ID_LEN];
	tetris::t_unique userUnique;

	UserInfo() {}
	explicit UserInfo(const tetris::t_unique userUnique, const char* name)
		:userUnique(userUnique)
	{
		assert(ID_LEN > strlen(name));
		strncpy(this->name, name, 10);
	}
}UserInfo;

typedef struct RoomInfo
{
	tetris::t_time makeTime;
	char roomName[ROOMNAME_LEN];
	tetris::t_unique unique;
	size_t roomNumber;
	size_t fullUserCount;
	size_t currentUserCount;

	RoomInfo() {}
	RoomInfo(const RoomInfo& other)
	:RoomInfo(other.unique, other.makeTime, other.roomName, other.roomNumber, other.fullUserCount, other.currentUserCount)
	{

	}

	explicit RoomInfo(const tetris::t_unique unique, const time_t makeTime, const char* roomName
	,const size_t roomnumber, const size_t fullusercount, const size_t currentusercount)
		:unique(unique), makeTime(makeTime)
		, roomNumber(roomnumber), fullUserCount(fullusercount), currentUserCount(currentusercount)
	{
		assert(ROOMNAME_LEN > strlen(roomName));
		strncpy(this->roomName, roomName, 10);
	}
}RoomInfo;

#pragma pack(pop)
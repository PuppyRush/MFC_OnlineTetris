﻿#pragma once

#pragma pack(push,4)
#pragma warning(push, disable:4996) //4996 for _CRT_SECURE_NO_WARNINGS equivalent#

#include <cassert>
#include <algorithm>
#include <memory.h>
#include <iterator>
#include <numeric>
#include <limits>
#include <type_traits>

#include "DefineInfo.h"
#include "structs.h"

#undef GetMessage
#undef min
#undef max

template <class T>
static void CopyChars(T *dest, const size_t destlen, const T *src, const size_t srclen)
{
	assert(destlen >= srclen);

	memset(dest, 0, sizeof(T)*destlen);
	memcpy(dest, src, srclen);
}

template <class T, size_t SIZE1, size_t SIZE2>
static void CopyChars(T dest[SIZE1][SIZE2], const T(*src)[SIZE2], const size_t src_dimension1, const size_t src_dimension2)
{
	assert(SIZE1 >= src_dimension1);
	assert(SIZE2 >= src_dimension2);

	memset(dest, 0, sizeof(T)*SIZE1*SIZE2);
	memcpy(dest, src, sizeof(T)*SIZE1*SIZE2);
	/*for (size_t i = 0; i < src_dimension1; i++)
		memcpy(dest[i], src[i], src_dimension2);*/
}

template <class T, size_t SIZE1, size_t SIZE2, size_t SIZE3>
static void CopyChars(T dest[SIZE1][SIZE2][SIZE3], const T(*src)[SIZE2][SIZE3], const size_t src_dimension1, const size_t src_dimension2, const size_t src_dimension3)
{
	assert(SIZE1 >= src_dimension1);
	assert(SIZE2 >= src_dimension2);
	assert(SIZE3 >= src_dimension3);

	memset(dest, 0, sizeof(T)*SIZE1*SIZE2*SIZE3);
	memcpy(dest, src, sizeof(T)*SIZE1*SIZE2*SIZE3);
	/*for (size_t i = 0; i < src_dimension1; i++)
		for (size_t l = 0; l < src_dimension2; l++)
			memcpy(dest[i][l], src[i][l], src_dimension3);*/
}

typedef struct Header
{
public:
	tetris::t_priority priority;
	tetris::t_msgidx msgIdx;
	tetris::t_msgsize size;

	Header() {}

	explicit Header(const tetris::t_priority prio, const tetris::t_msgidx msgIdx)
		:priority(prio), msgIdx(msgIdx)
	{}

	explicit Header(const tetris::t_priority prio, const tetris::t_msgidx msgIdx, const tetris::t_msgsize size)
		:priority(prio), msgIdx(msgIdx), size(size)
	{}

	static const tetris::t_msgidx getMsgidx(const char *msg)
	{
		tetris::t_msgidx msgidx = std::numeric_limits<tetris::t_msgidx>::max();
		memcpy(&msgidx, msg + sizeof(tetris::t_priority), sizeof(tetris::t_msgidx));
		return msgidx;
	}

	static const tetris::t_msgidx getMsgsize(const char *msg)
	{
		tetris::t_msgsize msgsize = std::numeric_limits<tetris::t_msgsize>::min();
		memcpy(&msgsize, msg + sizeof(tetris::t_priority) + sizeof(tetris::t_msgidx), sizeof(tetris::t_msgsize));
		return msgsize;
	}


	static tetris::t_priority getPriority(const char *msg)
	{
		tetris::t_priority priority = std::numeric_limits<tetris::t_priority>::max();
		memcpy(&priority, msg, sizeof(tetris::t_priority));
		return priority;
	}
}Header;

typedef struct Client
{
	tetris::t_unique unique;
	bool exceptme;
	char zero[3];

	Client() {}
	explicit Client(const tetris::t_unique unique, bool exception=false)
		:unique(unique), exceptme(exception)
	{}
	
}Client;

typedef struct mPermit : public Header
{
	tetris::t_property result;

	explicit mPermit(const Header h, const tetris::t_property res)
		:Header(h),
		 result(res)
	{
		size = sizeof(mPermit) - sizeof(h);
	}
}mPermit;

typedef struct mConnectionInfo : public Header
{
	tetris::t_unique userUnique;

	mConnectionInfo() {}
	explicit mConnectionInfo
	(
		const Header h,
		const tetris::t_unique userUnique
	)
		:Header(h),
		userUnique(userUnique)
	{
		size = sizeof(*this) - sizeof(h);
	}
}mConnectionInfo;

typedef struct mWaitingUserInfo : public Header
{
#define USER_LENGTH 8
    UserInfo userinfo[USER_LENGTH];
    size_t userInfoSize;
	tetris::t_unique unique;

	mWaitingUserInfo() {}
	explicit mWaitingUserInfo
	(
		const Header h,
		const tetris::t_unique unique,
		const UserInfo* _userinfo,
		const size_t userInfoSize
	)
	:Header(h),
		userInfoSize(userInfoSize),
		unique(unique)
	{
		assert(USER_LENGTH >= userInfoSize);
		memset(&userinfo, 0, sizeof(UserInfo)*USER_LENGTH);

		size = sizeof(*this) - sizeof(h);
		memcpy(&userinfo, _userinfo, sizeof(UserInfo)*userInfoSize);
	}
}mWaitingUserInfo;


typedef struct mWaitingGameRoomInfo : public Header
{
#define ROOM_LENGTH 2
    RoomInfo waitingRoom[ROOM_LENGTH];
    size_t waitingRoomSize;

	mWaitingGameRoomInfo() {}
	explicit mWaitingGameRoomInfo
	(
		const Header h,
		const RoomInfo* _roominfo,
		const size_t waitingRoomSize
	)
		:Header(h),
		waitingRoomSize(waitingRoomSize)
	{
		assert(ROOM_LENGTH >= waitingRoomSize);
		memset(&waitingRoom, 0, sizeof(RoomInfo)*ROOM_LENGTH);
		size = sizeof(*this) - sizeof(h);
		memcpy(&waitingRoom, _roominfo, sizeof(RoomInfo)*waitingRoomSize);
	}
}mWaitingRoomsInfo;


typedef struct mWaitingRoomInfo : public Header, Client
{
    RoomInfo roominfo;

    mWaitingRoomInfo() {}
    explicit mWaitingRoomInfo( const Header h,const RoomInfo roominfo   )
        :Header(h), roominfo(roominfo)
    {
    }
}mWaitingRoomInfo;


typedef struct mName : public Header, Client
{
    char name[ID_LEN];
    size_t namelen;

	mName()
	:Header(200, 0), namelen(0)
	{
		name[0] = 0;
	}

	explicit mName(const Header h, const tetris::t_unique unique, const size_t namelen, const char *name)
		:Header(h),
		Client(unique),
		namelen(namelen)
	{
		CopyChars(this->name, ID_LEN, name, namelen);
		size = sizeof(mName) - sizeof(h);
	}
}mName;

typedef struct mNames : public Header
{
    char name[MAX_ENTER][ID_LEN];
    size_t namelen[MAX_ENTER];
    const size_t enternum;

	explicit mNames(const Header h, const size_t enternum, const size_t *namelen, const char(*names)[ID_LEN])
		:Header(h), 
		enternum(enternum)
	{
		CopyChars<size_t>(this->namelen, size_t(MAX_ENTER), namelen, enternum);
		CopyChars<char, MAX_ENTER, ID_LEN>(this->name, names, enternum, ID_LEN);

		size = sizeof(mNames) - sizeof(h);
	}
}mNames;

typedef struct mChatMessage :public Header, Client
{
    char msg[MSG_LEN];
	size_t msglen;
	tetris::t_unique receiver;
	tetris::t_enum_chat chatType;

	mChatMessage(){}
	explicit mChatMessage(const Header h, const Client client, const size_t msglen, const char* msg, tetris::t_unique receiver, tetris::t_enum_chat chatType)
		:Header(h),
		Client(client),
		msglen(msglen),
		receiver(receiver),
		chatType(chatType)
	{
		CopyChars(this->msg, MSG_LEN, msg, msglen);
		size = sizeof(mChatMessage) - sizeof(h);
	}
}mChatMessage;

typedef struct mReady : public Header
{
	size_t namelen;
	char fromname[ID_LEN];
	bool ready;
	char zero;

	explicit mReady(const Header h, const size_t namelen, const char* fromname, const bool ready)
		:Header(h),
		ready(ready)
	{
		CopyChars(this->fromname, MSG_LEN, fromname, namelen);
		size = sizeof(*this) - sizeof(h);
	}
}mReady;

typedef struct mRadies : public Header
{
    char name[MAX_ENTER][ID_LEN];
    size_t namelen[MAX_ENTER];
    const size_t enternum;
	bool ready[MAX_ENTER];

	explicit mRadies(const Header h, const bool *ready, const int enternum, const size_t *namelen, 
		const char(*name)[ID_LEN])
		:Header(h), 
		enternum(enternum)
	{
		CopyChars(this->ready, MAX_ENTER, ready, enternum);
		CopyChars(this->namelen, MAX_ENTER, namelen, enternum);
		CopyChars<char, MAX_ENTER, ID_LEN>(this->name, name, enternum, ID_LEN);

		size = sizeof(this) - sizeof(h);
	}
}mRadies;

typedef struct mRoomInitInfo : public Header, Client
{
	RoomInfo roominfo;
	int map;
	int level;
	bool ghost;
	bool gravity;

	mRoomInitInfo() {}
	explicit mRoomInitInfo(const Header h, const tetris::t_unique unique, const RoomInfo roominfo, const int map, const int level, const bool ghost, const bool gravity)
		:Header(h), 
		Client(unique),
		roominfo(roominfo),
		map(map), 
		level(level), 
		ghost(ghost), 
		gravity(gravity)
	{
		size = sizeof(mRoomInitInfo) - sizeof(h);
	}
}mRoomInitInfo;

typedef struct mRoomInOutUser : public Header
{
	tetris::t_time time;
	UserInfo user;

	mRoomInOutUser() {}
	explicit mRoomInOutUser(const Header h, const UserInfo& user, const tetris::t_time time)
		:Header(h), 
		user(user),
		time(time)
	{}
}mRoomInOutUser;


typedef struct mMapstates : public Header
{
    int board[MAX_ENTER][VERNUM][HORNUM];
    char name[MAX_ENTER][ID_LEN];
    int namelen[MAX_ENTER];
    const size_t enternum;

	mMapstates(const Header h, const size_t enuternum, const int *namelen, char(*name)[ID_LEN], int(*board)[VERNUM][HORNUM])
		:Header(h), 
		enternum(enternum)
	{
		CopyChars(this->namelen, MAX_ENTER, namelen, enuternum);
		CopyChars<char, MAX_ENTER, ID_LEN>(this->name, name, enternum, ID_LEN);
		CopyChars<int, MAX_ENTER, VERNUM, HORNUM>(this->board, board, enternum, VERNUM, HORNUM);

		size = sizeof(mMapstates) - sizeof(h);
	}
}mMapstates;

typedef struct mMapstate : public Header
{
    int board[VERNUM][HORNUM];
    tPOINT figure[FG_FIXEDNUM];
    char name[ID_LEN];
    const size_t namelen;
	int kindfigure;

	mMapstate(const Header h, const size_t namelen, const char *name, const int board[VERNUM][HORNUM], const size_t kindfigure, const tPOINT figure[FG_FIXEDNUM])
		:Header(h), 
		namelen(namelen), 
		kindfigure(kindfigure)
	{
		CopyChars(this->name, ID_LEN, name, namelen);
		CopyChars<int, VERNUM, HORNUM>(this->board, board, VERNUM, HORNUM);
		CopyChars(this->figure, FG_FIXEDNUM, figure, FG_FIXEDNUM);

		size = sizeof(mMapstate) - sizeof(h);
	}
}mMapstate;

typedef struct mAddline : public Header
{
    char name[ID_LEN];
    size_t namelen;
	size_t linenum;

	mAddline(const Header h, const size_t namelen, const char *name, const size_t linenum)
		:Header(h), 
		namelen(namelen), 
		linenum(linenum)
	{
		CopyChars(this->name, ID_LEN, name, namelen);

		size = sizeof(mAddline) - sizeof(h);
	}
}mAddline;

#pragma warning(pop)
#pragma pack(pop)
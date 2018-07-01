#pragma once

#pragma warning(push)
#pragma warning(disable:4996) //4996 for _CRT_SECURE_NO_WARNINGS equivalent#

#include <cassert>
#include <algorithm>
#include <memory.h>
#include <iterator>
#include <numeric>
#include <limits>


#include "DefineInfo.h"
#include "structs.h"
#include "TType.h"
#include "TypeTraits.h"

#undef GetMessage
#undef min
#undef max

struct sender {};
struct receiver {};

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

	for (size_t i = 0; i < src_dimension1; i++)
		memcpy(dest[i], src[i], src_dimension2);
}

template <class T, size_t SIZE1, size_t SIZE2, size_t SIZE3>
static void CopyChars(T dest[SIZE1][SIZE2][SIZE3], const T(*src)[SIZE2][SIZE3], const size_t src_dimension1, const size_t src_dimension2, const size_t src_dimension3)
{
	assert(SIZE1 >= src_dimension1);
	assert(SIZE2 >= src_dimension2);
	assert(SIZE3 >= src_dimension3);

	memset(dest, 0, sizeof(T)*SIZE1*SIZE2*SIZE3);

	for (size_t i = 0; i < src_dimension1; i++)
		for (size_t l = 0; l < src_dimension2; l++)
			memcpy(dest[i][l], src[i][l], src_dimension3);
}

typedef struct Header : private sender
{
public:
	tetris::t_priority priority;
	tetris::t_msgidx msgIdx;
	tetris::t_msgsize size;

	explicit Header(const Priority prio, const tetris::t_msgidx msgIdx)
		:priority(toUType(prio)), msgIdx(msgIdx)
	{}

	explicit Header(const Priority prio, const tetris::t_msgidx msgIdx, const tetris::t_msgsize size)
		:priority(toUType(prio)), msgIdx(msgIdx), size(size)
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

	static Header getHeader(const char *msg)
	{
		return Header(toProperty( Header::getPriority(msg)), Header::getMsgidx(msg), Header::getMsgsize(msg));
	}
}Header;

typedef struct mEmpty : public Header
{
	mEmpty()
		:Header(Priority::VeryLow, toUType(SERVER_MSG::EMPTY_MESSAGE))
	{}
}mEmpty;



//�޼����� ���� ����ü
typedef struct mSendPermit : public Header
{
	size_t res;

	explicit mSendPermit(const Header h, const int res)
		:Header(h), 
		res(res)
	{
		size = sizeof(mSendPermit) - sizeof(h);
	}
}mSendPermit;

typedef struct mOnPermit : private receiver
{
	int res;
}mOnPermit;

typedef struct mSendConnectionInfo : public Header
{
	const tetris::t_userUnique userUnique;
	UserInfo userinfo[128];
	
	explicit mSendConnectionInfo
	(
		const Header h,
		const tetris::t_userUnique userUnique,
		const UserInfo* _userinfo,
		const size_t userInfoSize
	)
		:Header(h),
		userUnique(userUnique)
	{
		size = sizeof(*this) - sizeof(h);
		memcpy(&userinfo, _userinfo, userInfoSize);
	}
}mSendConnectionInfo;

typedef struct mOnConnectionInfo : public Header
{
	const tetris::t_userUnique userUnique;
	UserInfo userinfo[128];
}mOnConnectionInfo;


typedef struct mSendName : public Header
{
	size_t namelen;
	char name[ID_LEN];

	explicit mSendName(const Header h, const size_t namelen, const char *name)
		:Header(h), 
		namelen(namelen)
	{
		CopyChars(this->name, ID_LEN, name, namelen);
		size = sizeof(mSendName) - sizeof(h);
	}
}mSendName;

typedef struct mOnName : private receiver
{
	size_t namelen;
	char name[ID_LEN];
}mOnName;


typedef struct mSendNames : public Header
{
	const size_t enternum;
	size_t namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];

	explicit mSendNames(const Header h, const size_t enternum, const size_t *namelen, const char(*names)[ID_LEN])
		:Header(h), 
		enternum(enternum)
	{
		CopyChars<size_t>(this->namelen, size_t(MAX_ENTER), namelen, enternum);
		CopyChars<char, MAX_ENTER, ID_LEN>(this->name, names, enternum, ID_LEN);

		size = sizeof(mSendNames) - sizeof(h);
	}
}mSendNames;

typedef struct mOnNames : private receiver
{
	size_t enternum;
	size_t namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
}mOnNames;


typedef struct mSendMessage :public Header
{
	size_t msglen;
	char msg[MSG_LEN];

	explicit mSendMessage(const Header h, const size_t msglen, const char* msg)
		:Header(h)
	{
		CopyChars(this->msg, MSG_LEN, msg, msglen);
		size = sizeof(mSendMessage) - sizeof(h);
	}

	static mSendMessage GetMessage(const char* _msg)
	{
		auto len = strnlen(_msg, MSG_LEN);
		assert(len < MSG_LEN);

		char *msg = new char[MSG_LEN];
		memset(msg, 0, sizeof(char)*MSG_LEN);
		strncat(msg, _msg, len);

		const auto header = Header(Priority::Normal, toUType(SERVER_MSG::ON_MESSAGE));
		return mSendMessage(header, len, _msg);
	}
}mSendMessage;

typedef struct mOnMessage : private receiver
{
	size_t msglen;
	char msg[MSG_LEN];
}mOnMessage;


typedef struct mSendReady : public Header
{
	size_t namelen;
	char fromname[ID_LEN];
	bool ready;

	explicit mSendReady(const Header h, const size_t namelen, const char* fromname, const bool ready)
		:Header(h),
		ready(ready)
	{
		CopyChars(this->fromname, MSG_LEN, fromname, namelen);
		size = sizeof(*this) - sizeof(h);
	}
}mSendReady;

typedef struct mOnReady : private receiver
{
	size_t namelen;
	char fromname[ID_LEN];
	bool ready;
}mOnReady;


typedef struct mSendRadies : public Header
{
	const size_t enternum;
	size_t namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
	bool ready[MAX_ENTER];

	explicit mSendRadies(const Header h, const bool *ready, const int enternum, const size_t *namelen, 
		const char(*name)[ID_LEN])
		:Header(h), 
		enternum(enternum)
	{
		CopyChars(this->ready, MAX_ENTER, ready, enternum);
		CopyChars(this->namelen, MAX_ENTER, namelen, enternum);
		CopyChars<char, MAX_ENTER, ID_LEN>(this->name, name, enternum, ID_LEN);

		size = sizeof(this) - sizeof(h);
	}
}mSendRadies;

typedef struct mOnReadies : private receiver
{
	size_t enternum;
	size_t namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
	bool ready[MAX_ENTER];
}mOnReadies;


typedef struct mSendStartsignal : public Header
{
	const int map;
	const int level;
	const bool ghost;
	const bool gravity;

	explicit mSendStartsignal(const Header h, const int map, const int level, const bool ghost, const bool gravity)
		:Header(h), 
		map(map), 
		level(level), 
		ghost(ghost), 
		gravity(gravity)
	{
		size = sizeof(mSendStartsignal) - sizeof(h);
	}
}mSendStartsignal;

typedef struct mOnStartsignal : private receiver
{
	int map;
	int level;
	bool ghost;
	bool gravity;
}mOnStartsignal;


typedef struct mSendMapstates : public Header
{
	const size_t enternum;
	int namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
	int board[MAX_ENTER][VERNUM][HORNUM];

	mSendMapstates(const Header h, const size_t enuternum, const int *namelen, char(*name)[ID_LEN], int(*board)[VERNUM][HORNUM])
		:Header(h), 
		enternum(enternum)
	{
		CopyChars(this->namelen, MAX_ENTER, namelen, enuternum);
		CopyChars<char, MAX_ENTER, ID_LEN>(this->name, name, enternum, ID_LEN);
		CopyChars<int, MAX_ENTER, VERNUM, HORNUM>(this->board, board, enternum, VERNUM, HORNUM);

		size = sizeof(mSendMapstates) - sizeof(h);
	}
}mSendMapstates;

typedef struct mOnMapstates : private receiver
{
	size_t enternum;
	size_t namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
	int board[MAX_ENTER][VERNUM][HORNUM];
}mOnMapstates;


typedef struct mSendMapstate : public Header
{
	const size_t namelen;
	char name[ID_LEN];
	int board[VERNUM][HORNUM];
	int kindfigure;
	tPOINT figure[FG_FIXEDNUM];

	mSendMapstate(const Header h, const size_t namelen, const char *name, const int board[VERNUM][HORNUM], const size_t kindfigure, const tPOINT figure[FG_FIXEDNUM])
		:Header(h), 
		namelen(namelen), 
		kindfigure(kindfigure)
	{
		CopyChars(this->name, ID_LEN, name, namelen);
		CopyChars<int, VERNUM, HORNUM>(this->board, board, VERNUM, HORNUM);
		CopyChars(this->figure, FG_FIXEDNUM, figure, FG_FIXEDNUM);

		size = sizeof(mSendMapstate) - sizeof(h);
	}
}mSendMapstate;

typedef struct mOnMapstate : private receiver
{
	size_t namelen;
	char name[ID_LEN];
	int board[VERNUM][HORNUM];
	int kindfigure;
	tPOINT figure[FG_FIXEDNUM];
}mOnMapstate;


typedef struct mSendAddline : public Header
{
	size_t namelen;
	size_t linenum;
	char name[ID_LEN];

	mSendAddline(const Header h, const size_t namelen, const char *name, const size_t linenum)
		:Header(h), 
		namelen(namelen), 
		linenum(linenum)
	{
		CopyChars(this->name, ID_LEN, name, namelen);

		size = sizeof(mSendAddline) - sizeof(h);
	}
}mSendAddline;

typedef struct mOnAddline : private receiver
{
	size_t namelen;
	char name[ID_LEN];
	size_t linenum;
}mOnAddline;


#pragma warning(pop)
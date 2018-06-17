#pragma once

#pragma warning(push)
#pragma warning(disable:4996) //4996 for _CRT_SECURE_NO_WARNINGS equivalent
#pragma warning(disable:4091)

#define  _SCL_SECURE_NO_WARNINGS

#include <cassert>
#include <algorithm>
#include <memory.h>
#include <iterator>

#include "DefineInfo.h"
#include "structs.h"
#include "TType.h"

#undef GetMessage
#undef min
#undef max

namespace tetris
{

///////////////////////////////////////////////////////////////////////////////
//msg_idx//Ŭ���̾�Ʈ Ȥ�� ������ ���� �޼���
//IsServer//�޼����� ���� ��ü�� �������� Ŭ���̾�Ʈ ����?

struct client{};
struct server{};

template <class T>
static void CopyChars(T *dest, const size_t destlen, const T *src, const size_t srclen)
{
	assert(destlen >= srclen);

	memset(dest, 0, sizeof(T)*destlen);
	memcpy(dest, src, srclen);
}

template <class T, size_t SIZE1, size_t SIZE2>
static void CopyChars(T dest[SIZE1][SIZE2],	const T (*src)[SIZE2], const size_t src_dimension1, const size_t src_dimension2)
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
		for(size_t l = 0; l < src_dimension2; l++)
			memcpy(dest[i][l], src[i][l], src_dimension3);
}

typedef struct Header
{
public:
	t_priority priority;
	t_msgidx msgIdx;
	t_msgsize size;

	explicit Header(const size_t msgIdx)
		:msgIdx(msgIdx)
	{}

	explicit Header(const t_priority prio, const t_msgidx msgIdx, const t_msgsize size)
		:priority(prio), msgIdx(msgIdx), size(size)
	{}

	static const t_msgidx getMsgidx(const char *msg)
	{
		t_msgidx msgidx = std::numeric_limits<t_msgidx>::max();
		memcpy(&msgidx, msg + sizeof(t_priority), sizeof(t_msgidx));
		return msgidx;
	}

	static const t_msgidx getMsgsize(const char *msg)
	{
		t_msgsize msgsize = std::numeric_limits<t_msgsize>::min();
		memcpy(&msgsize, msg + sizeof(t_priority) + sizeof(t_msgidx), sizeof(t_msgsize));
		return msgsize;
	}


	static t_priority getPriorty(const char *msg)
	{
		t_priority priority = std::numeric_limits<t_priority>::max();
		memcpy(&priority, msg, sizeof(t_priority));
		return priority;
	}

	static Header get(const char *msg)
	{
		return Header(Header::getPriorty(msg), Header::getMsgidx(msg), Header::getMsgsize(msg));
	}
};

typedef struct mEmpty : public Header
{
	mEmpty()
		:Header(Header(0))
	{}
};

//�޼����� ���� ����ü
typedef struct mSendPermit : public Header
{
	size_t res;

	explicit mSendPermit(const Header h, const int res)
		:Header(h), res(res)
	{
		size = sizeof(mSendPermit) - sizeof(h);
	}
};

typedef struct mSendConnectionInfo : public Header
{
	const uint64_t uniqueOrder;

	explicit mSendConnectionInfo(const Header h, const uint64_t _uniqueOrder)
		:Header(h), uniqueOrder(_uniqueOrder)
	{
		size = sizeof(this) - sizeof(h);
	}
};

typedef struct mSendName : public Header
{
	int namelen;
	char name[ID_LEN];

	explicit mSendName(const Header h, const size_t namelen, const char *name)
		:Header(h), namelen(namelen)
	{
		CopyChars(this->name, ID_LEN, name, namelen);

		size = sizeof(mSendName) - sizeof(h);
	}
};

typedef struct mSendNames : public Header
{
	const size_t enternum;
	size_t namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
	
	explicit mSendNames(const Header h, const size_t enternum, const size_t *namelen, const char (*names)[ID_LEN] )
		:Header(h), enternum(enternum)
	{
		CopyChars<size_t>(this->namelen, size_t(MAX_ENTER), namelen, enternum);
		CopyChars<char,MAX_ENTER,ID_LEN>(this->name, names, enternum, ID_LEN);

		size = sizeof(mSendNames) - sizeof(h);
	}
};

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
		auto len = strnlen(_msg,MSG_LEN);
		assert(len < MSG_LEN);

		char *msg = new char[MSG_LEN];
		memset(msg, 0, sizeof(char)*MSG_LEN);
		strncat(msg, _msg,len);
			
		const auto header = Header(toUType(SERVER_MSG::ON_MESSAGE));
		return mSendMessage(header, len, _msg);
	}
};

typedef struct mSendReady : public Header
{
	size_t namelen;
	char fromname[ID_LEN];
	bool ready;

	explicit mSendReady(const Header h, const size_t namelen, const char* fromname, const bool ready)
		:Header(h), ready(ready)
	{
		CopyChars(this->fromname, MSG_LEN, fromname, namelen);
		size = sizeof(mSendReady) - sizeof(h);
	}
};

typedef struct mSendRadies : public Header
{
	const size_t enternum;
	size_t namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
	bool ready[MAX_ENTER];

	explicit mSendRadies(const Header h, const bool *ready, const int enternum, const size_t *namelen, const char (*name)[ID_LEN])
		:Header(h), enternum(enternum)
	{
		CopyChars(this->ready, MAX_ENTER, ready, enternum);
		CopyChars(this->namelen, MAX_ENTER, namelen, enternum);
		CopyChars<char, MAX_ENTER, ID_LEN>(this->name, name, enternum, ID_LEN);
			
		size = sizeof(this) - sizeof(h);
	}
};

typedef struct mSendStartsignal : public Header
{
	const int map;
	const int level;
	const bool ghost;
	const bool gravity;

	explicit mSendStartsignal(const Header h, const int map, const int level, const bool ghost, const bool gravity)
		:Header(h), map(map), level(level), ghost(ghost), gravity(gravity)
	{
		size = sizeof(mSendStartsignal) - sizeof(h);
	}
};

typedef struct mSendMapstates : public Header
{
	const size_t enternum;
	int namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
	int board[MAX_ENTER][VERNUM][HORNUM];

	mSendMapstates(const Header h, const size_t enuternum, const int *namelen, char(*name)[ID_LEN], int(*board)[VERNUM][HORNUM])
		:Header(h), enternum(enternum)
	{
		CopyChars(this->namelen, MAX_ENTER, namelen, enuternum);
		CopyChars<char, MAX_ENTER, ID_LEN>(this->name, name, enternum, ID_LEN);
		CopyChars<int, MAX_ENTER, VERNUM, HORNUM>(this->board, board, enternum, VERNUM, HORNUM);

		size = sizeof(mSendMapstates) - sizeof(h);
	}
};

typedef struct mSendMapstate : public Header
{
	const size_t namelen;
	char name[ID_LEN];
	int board[VERNUM][HORNUM];
	int kindfigure;
	tPOINT figure[FG_FIXEDNUM];

	mSendMapstate(const Header h, const size_t namelen, const char *name ,const int board[VERNUM][HORNUM], const size_t kindfigure, const tPOINT figure[FG_FIXEDNUM])
		:Header(h), namelen(namelen), kindfigure(kindfigure)
	{
		CopyChars(this->name, ID_LEN, name, namelen);
		CopyChars<int, VERNUM, HORNUM>(this->board, board, VERNUM, HORNUM);
		CopyChars(this->figure, FG_FIXEDNUM, figure, FG_FIXEDNUM);

		size = sizeof(mSendMapstate) - sizeof(h);
	}
};


typedef struct mSendAddline : public Header
{
	size_t namelen;
	size_t linenum;
	char name[ID_LEN];

	mSendAddline(const Header h,const size_t namelen,const char *name,const size_t linenum)
		:Header(h), namelen(namelen), linenum(linenum)
	{
		CopyChars(this->name, ID_LEN, name, namelen);

		size = sizeof(mSendAddline) - sizeof(h);
	}
};

////////////////////////////////////////////////////////////////////////////////

typedef struct mOnPermit 
{
	int res;
};

typedef struct mOnName 
{
	size_t namelen;
	char name[ID_LEN];
};

typedef struct mOnNames 
{
	size_t enternum;
	size_t namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
};

typedef struct mOnMessage 
{
	size_t msglen;
	char msg[MSG_LEN];
};

typedef struct mOnReady 
{
	size_t namelen;
	char fromname[ID_LEN];
	bool ready;
};

typedef struct mOnReadies 
{
	size_t enternum;
	size_t namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
	bool ready[MAX_ENTER];
};

typedef struct mOnStartsignal 
{
	int map;
	int level;
	bool ghost;
	bool gravity;
};


typedef struct mOnMapstate 
{
	size_t namelen;
	char name[ID_LEN];
	int board[VERNUM][HORNUM];
	int kindfigure;
	tPOINT figure[FG_FIXEDNUM];
};

typedef struct mOnMapstates 
{
	size_t enternum;
	size_t namelen[MAX_ENTER];
	char name[MAX_ENTER][ID_LEN];
	int board[MAX_ENTER][VERNUM][HORNUM];
};

typedef struct mOnAddline 
{
	size_t namelen;
	char name[ID_LEN];
	size_t linenum;
};

}

#pragma warning(pop)
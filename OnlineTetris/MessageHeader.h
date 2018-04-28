#pragma once

#include "DefineInfo.h"

namespace msg_header
{
	///////////////////////////////////////////////////////////////////////////////
	//msg_idx//클라이언트 혹은 서버가 받을 메세지
	//IsServer//메세지를 받을 주체가 서버인지 클라이언트 인지?

	template <class T>
	static void CopyChars(T *dest,const size_t destlen, const T *src,const size_t srclen)
	{
		ASSERT(destlen >= srclen);

		memset(dest, 0, sizeof(T)*destlen);
		std::copy_n(src, srclen, dest);
	}

	template <class T>
	static void CopyChars(T **dest, const size_t dest_dimension1, const size_t dest_dimension2, 
					const T **src, const size_t src_dimension1,const size_t src_dimension2)
	{
		ASSERT(dest_dimension1 >= src_dimension1);
		ASSERT(dest_dimension2 >= src_dimension2);

		memset(dest, 0, sizeof(T)*dest_dimension1*dest_dimension2);

		for(size_t i=0 ; i < src_dimension1 ; i++)
				std::copy_n(src[i], src_dimension2, dest[i]);
	}

	typedef struct Header
	{
		size_t msg_idx;
		size_t dataSize;
		explicit Header(const size_t msgIdx)
			:msg_idx(msgIdx)
		{}
	};

	//메세지를 보낼 구조체
	typedef struct mSendPermit : public Header
	{
		size_t res;
		mSendPermit(const Header h, const int res)
			:Header(h), res(res)
		{
			dataSize = sizeof(mSendPermit) - sizeof(h);
		}
	};

	typedef struct mSendName : public Header
	{
		int namelen;
		char name[ID_LEN];

		mSendName(const Header h, const int namelen, char name[ID_LEN])
			:Header(h), namelen(namelen)
		{
			CopyChars(this->name, ID_LEN, name, namelen);

			dataSize = sizeof(mSendName) - sizeof(h);
		}
	};

	typedef struct SEND_NAMES : public Header
	{
		const size_t enternum;
		size_t namelen[MAX_ENTER];
		char name[MAX_ENTER][ID_LEN];

		SEND_NAMES(const Header h, const size_t enternum, const size_t *namelen, const char **names)
			:Header(h), enternum(enternum)
		{
			CopyChars<size_t>(this->namelen, size_t(MAX_ENTER), namelen, enternum);
			CopyChars(this->name, size_t(MAX_ENTER), size_t(ID_LEN), names, 0, 0);
		}
	};

	typedef struct mSendMESSAGE {
		bool IsServer;
		int msg_idx;
		int struct_size;
		int msglen;
		char msg[MSG_LEN];
	};

	typedef struct SEND_READY {
		bool IsServer;
		int msg_idx;
		int struct_size;
		int namelen;
		char fromname[ID_LEN];
		bool ready;
	};

	typedef struct SEND_READIES {
		bool IsServer;
		int msg_idx;
		int struct_size;
		bool ready[MAX_ENTER];
		int enternum;
		int namelen[MAX_ENTER];
		char name[MAX_ENTER][ID_LEN];
	};

	typedef struct SEND_STARTSIGNAL {
		bool IsServer;
		int msg_idx;
		int struct_size;
		int map;
		int level;
		bool ghost;
		bool gravity;
	};



	typedef struct SEND_MAPSTATES {
		bool IsServer;
		int msg_idx;
		int struct_size;
		int enternum;
		int namelen[MAX_ENTER];
		char name[MAX_ENTER][ID_LEN];
		int board[MAX_ENTER][VERNUM][HORNUM];
	};

	typedef struct SEND_MAPSTATE {
		bool IsServer;
		int msg_idx;
		int struct_size;
		int namelen;
		char name[ID_LEN];
		int board[VERNUM][HORNUM];
		int kindfigure;
		POINT figure[FG_FIXEDNUM];
	};


	typedef struct SEND_ADDLINE {
		bool IsServer;
		int msg_idx;
		int struct_size;
		int namelen;
		char name[ID_LEN];
		int linenum;
	};

	////////////////////////////////////////////////////////////////////////////////

	typedef struct ON_PERMIT {

		int res;
	};

	typedef struct m_OnName {
		int namelen;
		char name[ID_LEN];

	};

	typedef struct ON_NAMES {
		int enternum;
		int namelen[MAX_ENTER];
		char name[MAX_ENTER][ID_LEN];
	};


	typedef struct mOnMESSAGE {

		int msglen;
		char msg[MSG_LEN];
	};

	typedef struct m_OnReady {
		int namelen;
		char fromname[ID_LEN];
		bool ready;
	};


	typedef struct ON_READIES {
		bool ready[MAX_ENTER];
		int enternum;
		int namelen[MAX_ENTER];
		char name[MAX_ENTER][ID_LEN];
	};

	typedef struct ON_STARTSIGNAL {
		int map;
		int level;
		bool ghost;
		bool gravity;
	};


	typedef struct m_OnMapstate {
		int namelen;
		char name[ID_LEN];
		int board[VERNUM][HORNUM];
		int kindfigure;
		POINT figure[FG_FIXEDNUM];
	};

	typedef struct m_OnMapstates {
		int enternum;
		int namelen[MAX_ENTER];
		char name[MAX_ENTER][ID_LEN];
		int board[MAX_ENTER][VERNUM][HORNUM];
	};

	typedef struct m_OnAddLine {

		int namelen;
		char name[ID_LEN];
		int linenum;
	};

}
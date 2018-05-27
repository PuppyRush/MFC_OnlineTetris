#pragma once

#include <string>

#undef POINT

using namespace std;

class IPString
{
private:
	string ip;

public:

	IPString()
	{
		IPString({192,168,0,1});
	}

	explicit IPString(initializer_list<size_t> fields)
	{
		_ASSERT(fields.size() == 4);
		ip.reserve(16);

		for(auto b : fields)
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
};

typedef struct tPOINT
{
	long x;
	long y;
} ;


typedef struct FIGURE
{
	tPOINT FgInfo[4];		//*************************************DefineInfo.h�� �����Ǿ���� ����
	tPOINT end;				//���� ���ʾƷ��� ��ǥ�� �����Ѵ�.
	int Figure, NextFigure;
	int Height;
	int Width;
	int dir;
};

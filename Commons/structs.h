#pragma once

#include <string>
#include <cassert>

#undef POINT

using namespace std;

class uncopyable
{
protected:
	uncopyable(){}
	virtual ~uncopyable(){}
private:
	void operator=(const uncopyable&) = delete;
	uncopyable(const uncopyable &) = delete;
	uncopyable(const uncopyable *) = delete;
	uncopyable(const uncopyable &&) = delete;

};

class IPString
{

public:
	IPString()
	{
		IPString({192,168,0,1});
	}

	explicit IPString(initializer_list<size_t> fields)
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
	string ip;
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

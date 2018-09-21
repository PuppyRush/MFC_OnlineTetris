#pragma once
class StringManager
{
public:
	StringManager();
	~StringManager();

	static CString ToCStringFrom(const string &);
	static string ToStringFrom(const CString &);

	static string ToStringFrom(const int val)
	{
		char buf[200];
		memset(buf, 0, 200);
		sprintf(buf, "%d", val);
		return string(buf);
	}

	static CString ToCStringFrom(const int val)
	{
		char buf[200];
		memset(buf, 0, 200);
		sprintf(buf, "%d", val);
		return CString(buf);
	}
};


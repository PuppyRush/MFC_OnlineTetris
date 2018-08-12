#pragma once
class StringManager
{
public:
	StringManager();
	~StringManager();

	static CString ToCStringFrom(const string &);
	static string ToStringFrom(const CString &);
};


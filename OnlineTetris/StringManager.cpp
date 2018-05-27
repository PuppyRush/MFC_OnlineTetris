#include "stdafx.h"
#include "StringManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

StringManager::StringManager()
{
}


StringManager::~StringManager()
{
}

string StringManager::ToStringFrom(const CString &str)
{
	int len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	char *chars= new char[len+1];
	WideCharToMultiByte(CP_ACP, 0, str, -1, chars, len, NULL, NULL);

	return string(chars);
}

CString StringManager::ToCStringFrom(const string &str)
{
	return CString(str.c_str());
}
#pragma once

#include "OnlineTetris.h"
#include <regex>

class Validator
{

public:
	Validator();
	~Validator();

	//static string errmsg;

	//static const string GetLastMessage() { return errmsg; }

	static bool IdCheck(const string &id, const size_t min, const size_t max);
};

//string Validator::errmsg = "";
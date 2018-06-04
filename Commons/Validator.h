#pragma once

#include <regex>
#include <string>

using namespace std;

namespace validator
{
	bool IdCheck(const string &id, const size_t min, const size_t max);
}



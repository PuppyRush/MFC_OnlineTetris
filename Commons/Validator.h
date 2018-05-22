#pragma once

#include <regex>
#include <string>

using namespace std;

namespace validator
{
	bool IdCheck(const string &id, const size_t min, const size_t max)
	{
		string reg;
		reg.reserve(50);
		reg.append("[°¡-ÆR|\\w]{");
		reg.append(to_string(min));
		reg.append(",");
		reg.append(to_string(max));
		reg.append("}");

		if (!std::regex_search(id, std::regex(reg)))
		{
			//errmsg = "¾ÆÀÌµğ´Â ¿µ¾î 1~10ÀÚ ÇÑ±Û 5~10ÀÚ¸¸ °¡´ÉÇÕ´Ï´Ù.";
			return false;
		}
		else
			return true;
	}
}



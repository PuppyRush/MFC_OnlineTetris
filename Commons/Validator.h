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
		reg.append("[��-�R|\\w]{");
		reg.append(to_string(min));
		reg.append(",");
		reg.append(to_string(max));
		reg.append("}");

		const auto regex_str = std::regex(reg);

		if (!std::regex_search(id, regex_str))
		{
			//errmsg = "���̵�� ���� 1~10�� �ѱ� 5~10�ڸ� �����մϴ�.";
			return false;
		}
		else
			return true;
	}
}



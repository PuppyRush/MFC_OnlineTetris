#include "Validator.h"

#include <regex>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const bool idCheck(const std::string &id, const size_t min, const size_t max)
{
	std::string reg;
	reg.reserve(50);
	reg.append("[��-�R|\\w]{");
	reg.append(std::to_string(min));
	reg.append(",");
	reg.append(std::to_string(max));
	reg.append("}");

	const auto _regex = std::regex(reg);
	if (!std::regex_search(id, _regex))
	{
		//errmsg = "���̵�� ���� 1~10�� �ѱ� 5~10�ڸ� �����մϴ�.";
		return false;
	}
	else
		return true;
}

const bool stringLengthCheck(const std::string str, const size_t min, const size_t max)
{
	const size_t size = str.size();
	return (min <= size && size <= max);
}
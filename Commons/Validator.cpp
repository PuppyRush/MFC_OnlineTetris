#include "Validator.h"

using namespace validator;

bool validator::IdCheck(const string &id, const size_t min, const size_t max)
{
	string reg;
	reg.reserve(50);
	reg.append("[��-�R|\\w]{");
	reg.append(to_string(min));
	reg.append(",");
	reg.append(to_string(max));
	reg.append("}");

	if (!std::regex_search(id, std::regex(reg)))
	{
		//errmsg = "���̵�� ���� 1~10�� �ѱ� 5~10�ڸ� �����մϴ�.";
		return false;
	}
	else
		return true;
}

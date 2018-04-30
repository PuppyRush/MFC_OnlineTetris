#pragma once

#include <string>

using namespace std;

class IPString
{
private:
	string ip;

public:
	explicit IPString(initializer_list<size_t> fields)
	{
		_ASSERT(fields.size() == 4);
		ip.reserve(16);

		for each(auto b in fields)
		{
			ip.append(std::to_string(static_cast<long>(b)));
			ip.append(".");
		}
	}

	const char* GetString()
	{
		return ip.c_str();
	}
};
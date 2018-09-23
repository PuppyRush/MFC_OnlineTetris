#pragma once

#include <unordered_set>
#include <queue>
#include "TType.h"

class Chat
{
public:
	Chat();
	~Chat();

	void addFilter(const tetris::t_unique unique);
	void add(const std::string str);


private:

	std::unordered_set<tetris::t_unique> m_filter;
	std::queue<std::string> m_chatQ;

};


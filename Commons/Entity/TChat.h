#pragma once

#include <unordered_set>
#include <queue>
#include "../TType.h"

class TChat
{
public:
	TChat();
	virtual ~TChat();

	void removeFilter(const tetris::t_unique);
	void addFilter(const tetris::t_unique);
	void add(const std::string str);
	void addWhisper(const std::string str);
	void clear();
private:
	std::unordered_set<tetris::t_unique> m_filter;
	std::deque<std::string> m_chatQ;

};


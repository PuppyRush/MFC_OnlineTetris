#pragma once

#include <unordered_set>
#include <queue>
#include "../TType.h"

class TChat
{
public:

	enum class property_chat : tetris::t_enum_chat
	{
		Begin = static_cast<tetris::t_enum_chat>(1) << 0,
		SendMsg = Begin << 0,
		RecvMsg = Begin << 1,
		SendWhisper = Begin << 2,
		RecvWhisper = Begin << 3,
		AddFilter = Begin << 4,
		RemoveFilter = Begin << 5,
		End = Begin << 6
	};

	TChat();
	virtual ~TChat();

	void removeFilter(const tetris::t_unique);
	void addFilter(const tetris::t_unique);
	void add(const tetris::t_unique sender, const std::string& str);
	void addWhisper(const tetris::t_unique sender, const tetris::t_unique reciver, const std::string& str);
	void clear();

private:
	std::unordered_set<tetris::t_unique> m_filter;
	std::deque<std::string> m_chatQ;

};


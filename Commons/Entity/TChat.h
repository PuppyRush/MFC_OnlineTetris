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
		SendMessage = Begin << 0,
		RecvMessage = Begin << 1,
		AddFilter = Begin << 2,
		RemoveFilter = Begin << 3,
		Whisper = Begin << 4,
		End = Begin << 5
	};

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


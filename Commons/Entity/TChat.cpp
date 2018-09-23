#include "TChat.h"



TChat::TChat()
{
}


TChat::~TChat()
{
}

void TChat::removeFilter(const tetris::t_unique unique)
{
	if (m_filter.count(unique))
		m_filter.erase(unique);
}

void TChat::addFilter(const tetris::t_unique unique)
{
	m_filter.insert(unique);
}
void TChat::add(const std::string str)
{
	m_chatQ.push_back(str);
}

void TChat::addWhisper(const std::string str)
{
}
void TChat::clear()
{
	m_chatQ.clear();
}
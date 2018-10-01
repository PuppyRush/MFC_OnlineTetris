#include "TUser.h"
#include "TSocket.h"

#include <memory.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TetrisUser::TetrisUser(const tetris::t_socket socket)
	:m_chat(std::make_shared<TChat>()),
	m_socketUnique(socket)
{}

void TetrisUser::removeFilter(const tetris::t_unique unique)
{
	m_chat->removeFilter(unique);
}

void TetrisUser::addFilter(const tetris::t_unique unique)
{
	m_chat->addFilter(unique);
}
void TetrisUser::add(const std::string str)
{
	m_chat->add(str);
}

void TetrisUser::addWhisper(const std::string str)
{
	m_chat->addWhisper(str);
}
void TetrisUser::clear()
{
	m_chat->clear();
}
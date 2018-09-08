#include "TMessageSender.h"



TMessageSender::TMessageSender()
	:m_isContinue(true)
{
}


TMessageSender::~TMessageSender()
{
	m_isContinue = false;
}

//
// Created by pi on 9/3/18.
//

#include "TMessageObject.h"


TMessageObject::TMessageObject(const tetris::t_priority priority, const tetris::t_msgsize size, const char* msg)
:m_priority(priority), m_size(size), m_message(msg)
{
}
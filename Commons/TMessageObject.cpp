//
// Created by pi on 9/3/18.
//
#include <numeric>
#include "TMessageObject.h"

TMessageObject::TMessageObject(const tetris::t_socket socket, const bool exception, const tetris::t_priority priority, const tetris::t_msgsize size, const char* msg)
    :m_sender(socket), m_priority(priority), m_size(size), m_message(msg), m_exceptme(exception),m_broadcast(true)
{
}

TMessageObject::TMessageObject(const bool exception, const tetris::t_priority priority, const tetris::t_msgsize size, const char* msg)
    :m_sender(std::numeric_limits<tetris::t_socket>::max()), m_priority(priority), m_size(size), m_message(msg), m_exceptme(exception)
    ,m_broadcast(true)
{
}

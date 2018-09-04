//
// Created by pi on 9/3/18.
//

#pragma once

#include <cassert>

#include "DefineInfo.h"
#include "Entity/TObject.h"
#include "TType.h"

class TMessageObject : public TObject
{
public:

    TMessageObject(const tetris::t_priority, const tetris::t_msgsize , const char* msg);

    template <class T>
    static const T toMessage(const TMessageObject& msg)
    {
        T message;
        memcpy(&message, msg.getMessage(), msg.getSize());
        return message;
    }


    template <class T>
    static const TMessageObject toMessage(T *msg)
    {
        const size_t len = sizeof(T);
        assert(PACKET_LEN > len);

        char* dest = new char[PACKET_LEN];
        memcpy(dest, msg, PACKET_LEN);
        dest[len] = 0;

        tetris::t_priority priority = msg->priority;
        return TMessageObject(priority, len, dest);
    }

    inline bool operator<(const TMessageObject &msg) const noexcept
    {return this->m_priority < msg.m_priority;}

    inline bool operator>(const TMessageObject &msg) const noexcept
    {return this->m_priority > msg.m_priority;}

    inline const char* getMessage() const noexcept { return m_message;}
    inline const tetris::t_msgsize getSize() const noexcept { return m_size;}

private:
    tetris::t_priority m_priority;
    tetris::t_msgsize m_size;
    tetris::t_msgidx m_msgidx;
    const char* m_message;

    tetris::t_dist m_dest;
};


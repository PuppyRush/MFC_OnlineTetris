//
// Created by pi on 9/3/18.
//

#pragma once

#include <cassert>

#include "TMessageStruct.h"
#include "DefineInfo.h"
#include "TType.h"

class TMessageObject
{
public:

    template <class T>
    static const T toMessage(const TMessageObject& msg)
    {
        T message;
        memcpy(&message, msg.getMessage(), msg.getSize());
        return message;
    }

	template <class T>
	static const TMessageObject toMessage(const tetris::t_socket sender, T *msg)
	{
		const size_t len = sizeof(T);
		assert(PACKET_LEN > len);

		char* dest = new char[PACKET_LEN];
		memcpy(dest, msg, PACKET_LEN);
		dest[len] = 0;

		tetris::t_priority priority = msg->priority;
		return TMessageObject(sender, false, priority, len, dest);
	}

	/*template <class T, typename std::enable_if_t<std::is_base_of_v<Client, T>,T>>
    static const TMessageObject toMessage(const tetris::t_socket sender, T *msg)
    {
        const size_t len = sizeof(T);
        assert(PACKET_LEN > len);

        char* dest = new char[PACKET_LEN];
        memcpy(dest, msg, PACKET_LEN);
        dest[len] = 0;

        tetris::t_priority priority = msg->priority;
		const bool exceptionme = msg->exceptme;
        return TMessageObject(sender, false, priority, len, dest);
    }*/

	inline static const TMessageObject toMessage(const tetris::t_socket socket, const char *msg, const tetris::t_msgsize size)
	{
		const auto prio = Header::getPriority(msg);
		return TMessageObject(socket, false, prio, size, msg);
	}

	inline static const TMessageObject emptyMessage(const tetris::t_socket socket)
	{
		return TMessageObject(socket, false, static_cast<tetris::t_priority>(Priority::VeryLow), 0, nullptr);
	}

    inline bool operator<(const TMessageObject &msg) const noexcept
    {return this->m_priority < msg.m_priority;}

    inline bool operator>(const TMessageObject &msg) const noexcept
    {return this->m_priority > msg.m_priority;}

	inline const tetris::t_socket getSocket() const noexcept {	return m_sender;}
	inline const tetris::t_dist getDistinguish() const noexcept { return m_dest; }
    inline const char* getMessage() const noexcept { return m_message;}
    inline const tetris::t_msgsize getSize() const noexcept { return m_size;}
	inline const bool isExceptionMe() const noexcept { return m_exceptme; }

private:
	tetris::t_socket m_sender;
	bool m_exceptme;

    tetris::t_priority m_priority;
    tetris::t_msgsize m_size;
    tetris::t_msgidx m_msgidx;
    const char* m_message;

    tetris::t_dist m_dest;

	explicit TMessageObject(const tetris::t_socket socket, const bool exception, const tetris::t_priority, const tetris::t_msgsize, const char* msg);
};


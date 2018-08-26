#pragma once

#include "TType.h"
#include "DefineInfo.h"
#include "MessageHeader.h"

template<class T>
constexpr const auto toUType(T enuml) noexcept
{
	return static_cast<std::underlying_type_t<T>>(enuml);
}


struct msgHelper
{
	enum class eElementvalue : uint8_t
	{
		priority = 0,
		message = 1,
		size = 2
	};

	inline static const tetris::msgElement getEmptyMessage()
	{
		static tetris::msgElement empty = tetris::msgElement(0, 0, 0);
		return empty;
	}

	static constexpr tetris::msgElement getMsgElement(const tetris::t_priority prio, const char* msg, const size_t size)
	{
		return std::make_tuple(prio, msg, size);
	}

	static constexpr const auto getPriority(const tetris::msgElement &msg) noexcept
	{
		return std::get<toUType(eElementvalue::priority)>(msg);
	}

	static constexpr auto getMessage(const tetris::msgElement &msg) noexcept
	{
		return std::get<toUType(eElementvalue::message)>(msg);
	}

	static constexpr const auto getSize(const tetris::msgElement &msg) noexcept
	{
		return std::get<toUType(eElementvalue::size)>(msg);
	}
	
};

template <class T>
const T toMessage(const tetris::msgElement &msg)
{
	static size_t headerSize = sizeof(Header);
	T message;
	memcpy(&message, msgHelper::getMessage(msg)+headerSize, msgHelper::getSize(msg)-headerSize);
	return message;
}


constexpr const Priority toProperty(const tetris::t_priority priority) noexcept
{
	switch (priority)
	{
		case 1000:
			return Priority::VeryHigh;
		case 800:
			return Priority::High;
		case 600:
			return Priority::Normal;
		case 400:
			return Priority::Low;
		case 200:
			return Priority::VeryLow;
		default:
			return Priority::VeryLow;
	}
}

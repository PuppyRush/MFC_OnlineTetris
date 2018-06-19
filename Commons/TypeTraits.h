#pragma once

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
	const auto charMsg = msgHelper::getMessage(msg);
	T message;
	memcpy(&message, charMsg, msgHelper::getSize(msg));
	return message;
}

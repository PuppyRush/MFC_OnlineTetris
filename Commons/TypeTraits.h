#pragma once

#include <set>
#include <numeric>

#include "TType.h"
#include "TProperty.h"
#include "DefineInfo.h"
#include "TMessageStruct.h"

template<class T>
constexpr const auto toUType(T enuml) noexcept
{
	return static_cast<std::underlying_type_t<T>>(enuml);
}

constexpr const Priority toPriority(const tetris::t_priority priority) noexcept
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

constexpr const tetris::t_priority toPriority(const Priority priority) noexcept
{
    return toUType(priority);
}

template <class T>
struct EnumIterator
{
	T value;

	EnumIterator()
		:value(T::Begin)
	{}

	inline const T begin() noexcept
	{
		value = static_cast<T>( toUType(value) << 1);
		return value;
	}

	inline const bool end() const noexcept
	{
		return toUType(value) != toUType(T::End);
	}

	EnumIterator operator++()
	{
		value = (T)(toUType(value) << 1);
		return *this;
	}
	
	bool operator!=(const EnumIterator *other)
	{
		return toUType(value) != toUType(other->value);
	}
};

//const std::set<tetris::t_dist> toDistinguish(const tetris::t_dist dist)
//{
//	std::set<tetris::t_dist> distset;
//	constexpr size_t maxi = sizeof(dist) * 8;
//	for (size_t d = 0u; d < maxi; d++)
//	{
//		const auto shifted = 1ull << d;
//		if (dist & shifted)
//			distset.insert(shifted);
//	}
//	return distset;
//}

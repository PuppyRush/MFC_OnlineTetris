#pragma once

#include <tuple>
#include <atomic>>

namespace tetris_type
{
	using namespace std;

	using portType = unsigned short;

	using priorityType = unsigned short;
	using msgidxType = unsigned short;
	using msgsizeType = unsigned int;
	using headerType  = unsigned short;

	using msgElement = std::tuple<priorityType, const char*, size_t>;
	using elementEnumBase  = std::uint8_t;

	using tUnique = std::atomic_uint_fast16_t;
}

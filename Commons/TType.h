
#pragma once

#include <atomic>
#include <tuple>
#include <memory>

namespace tetris
{
	using t_port = unsigned short;
	using t_socket = unsigned int;

	using t_priority = unsigned short;
	using t_msgidx = unsigned short;
	using t_msgsize = unsigned int;
	using t_header  = unsigned short;

	using msgElement = std::tuple<t_priority, const char*, size_t>;

	using t_unique = uint_fast16_t;
	using t_roomUniqueAtomic = std::atomic<t_unique>;
	using t_roomUnique = uint_fast16_t;
	using t_uniqueAtomic = std::atomic<t_unique>;
}
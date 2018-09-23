#pragma once

#include <atomic>
#include <tuple>
#include <memory>

namespace tetris
{
	using t_port = unsigned short;
	using t_socket = int;

	using t_priority = unsigned short;
	using t_msgidx = unsigned short;
	using t_msgsize = unsigned int;
	using t_header  = unsigned short;
	using t_error = unsigned short;
	using t_property = unsigned short;
	using t_dist = unsigned short;

	using t_time = unsigned long long ;

	using t_unique = std::uint_fast16_t ;
	using t_uniqueAtomic = std::atomic<t_unique>;

	template <class T>
	using t_ptr = std::shared_ptr<T>;

	using t_enum_chat = std::uint16_t;
}

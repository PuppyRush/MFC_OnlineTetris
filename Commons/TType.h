#pragma once

#include <tuple>
#include <atomic>

using namespace std;

namespace tetris
{
	using t_port = unsigned short;
	using t_socket = unsigned int;

	using t_priority = unsigned short;
	using t_msgidx = unsigned short;
	using t_msgsize = unsigned int;
	using t_header  = unsigned short;

	using msgElement = std::tuple<t_priority, const char*, size_t>;

	using t_unique = std::uint_fast16_t;
	using t_uniqueAtomic = std::atomic<t_unique>;

	template <class T>
	using t_sptr = std::shared_ptr<T>;
}
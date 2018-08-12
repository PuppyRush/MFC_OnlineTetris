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
	using t_error = unsigned short;
	using t_property = unsigned short;

	using msgElement = std::tuple<t_priority, const char*, size_t>;

	template <class T>
	using t_uniqueAtomic = std::atomic<T>;

	using t_socketUnique = t_socket;
	using t_userUnique = uint_fast16_t;
	using t_userUniqueAtomic = t_uniqueAtomic<t_userUnique>;
	using t_roomUnique = uint_fast16_t;
	using t_roomUniqueAtomic = t_uniqueAtomic<t_roomUnique>;

	template <class T>
	using t_ptr = std::shared_ptr<T>;
}

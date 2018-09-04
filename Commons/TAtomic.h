#pragma once

#include <atomic>

#include "TType.h"

class TAtomic
{
public:
	~TAtomic()
	{}

	static const tetris::t_unique newUnique() noexcept
	{
		static tetris::t_uniqueAtomic _atomic;
		return _atomic.fetch_add(1);
	}

private:
	TAtomic()	{}
};


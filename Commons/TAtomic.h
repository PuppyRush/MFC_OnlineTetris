#pragma once

#include <atomic>

#include "TType.h"

template <class T>
class TAtomic
{
public:
	TAtomic()
		:m_unique(0)
	{
	}

	~TAtomic()
	{}

	const T newUnique() noexcept
	{
		m_unique.fetch_add(1);
		return m_unique.load();
	}

	const T getUnique() const noexcept
	{
		return m_unique.load();
	}

private:
	tetris::t_uniqueAtomic<T> m_unique;
};


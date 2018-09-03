#pragma once

#include <memory>
#include "../TAtomic.h"
#include "../TType.h"

class TObject
{
public:
	TObject();
	virtual ~TObject() {}

	inline const bool operator==(const TObject& object) const noexcept
	{	return this->getUnique() == object.getUnique();}

	inline const bool operator!=(const TObject& object) const noexcept
	{	return this->getUnique() != object.getUnique();}

	inline const tetris::t_unique getUnique() const noexcept
	{ return m_unique;	}

private:
	tetris::t_unique m_unique;
};
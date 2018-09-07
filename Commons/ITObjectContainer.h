#pragma once

#include "Uncopyable.h"
#include "TType.h"

class ITObjectContainer : public Uncopyable
{
public:


protected:
	ITObjectContainer(tetris::t_dist dist)
		:m_dist(dist) 
	{}

	tetris::t_dist m_dist;
};
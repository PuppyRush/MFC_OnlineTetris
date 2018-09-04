#pragma once

#include <memory>

#include "../Uncopyable.h"

class TObject : private Uncopyable
{
public:
	virtual ~TObject() {}



};
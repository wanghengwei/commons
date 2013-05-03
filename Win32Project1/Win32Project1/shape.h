#pragma once
#include "point.h"

class shape
{
public:
	shape();

	virtual ~shape();

	virtual void position(point_t const &base_pos)
	{

	}

	virtual bool contains(point_t const &) const
	{
		return false;
	}
};


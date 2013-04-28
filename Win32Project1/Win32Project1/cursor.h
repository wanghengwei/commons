#pragma once
#include "point.h"

struct cursor_t
{
	point_t position;

	cursor_t& set_pos(LPARAM lp);
};
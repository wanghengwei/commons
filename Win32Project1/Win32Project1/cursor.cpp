#include "stdafx.h"
#include "cursor.h"

cursor_t& cursor_t::set_pos(LPARAM lp)
{
	position.x = GET_X_LPARAM(lp);
	position.y = GET_Y_LPARAM(lp);

	return *this;
}
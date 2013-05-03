#pragma once
#include "point.h"

class mouse_pointer
{
	point_t m_position;

	bool m_left_down;

	bool m_right_down;

public:
	mouse_pointer() : m_left_down(false), m_right_down(false) {}

	mouse_pointer& position(int x, int y) 
	{
		m_position.x = x;
		m_position.y = y;

		return *this;
	}

	point_t& position() { return m_position; }

	point_t const & position() const { return m_position; }

	void left_down(bool b) { m_left_down = b; }

	bool is_left_down() const { return m_left_down; }
};
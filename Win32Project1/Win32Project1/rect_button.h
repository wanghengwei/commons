#pragma once
#include "button.h"
#include "rect.h"

class rect_button : public button, protected rect_t
{
	HBRUSH m_nor_brush;
	HBRUSH m_hot_brush;
	HBRUSH m_shadow_brush;
public:
	rect_button(window *parent) : button(parent), rect_t(0, 60, 0, 30), m_nor_brush(CreateSolidBrush(RGB(0, 150, 150))), m_hot_brush(CreateSolidBrush(RGB(0, 200, 200))), m_shadow_brush(CreateSolidBrush(RGB(0, 0, 0))) {}

	void render(HDC, PAINTSTRUCT const&) override;

	bool is_hot() const override;

	void position(point_t const& p)
	{
		int h = height();
		int w = width();

		lb_conor = p;
		rt_conor.x = lb_conor.x + w;
		rt_conor.y = lb_conor.y + h;
	}

	void position(int x, int y)
	{
		position(point_t(x, y));
	}
};
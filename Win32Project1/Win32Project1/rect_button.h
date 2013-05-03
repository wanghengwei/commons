#pragma once
#include "button.h"
#include "rect.h"

class rect_button : public button, public rect_t
{
	HBRUSH m_nor_brush;
	HBRUSH m_hot_brush;
	HBRUSH m_shadow_brush;
public:
	rect_button(std::string const &id, widget *parent) : button(id, parent), rect_t(0, 60, 0, 30), m_nor_brush(CreateSolidBrush(RGB(0, 150, 150))), m_hot_brush(CreateSolidBrush(RGB(0, 200, 200))), m_shadow_brush(CreateSolidBrush(RGB(0, 0, 0))) {}

	void react_state() override;

	void render(HDC, PAINTSTRUCT const&) override;

private:
	rect_t shadow_face()
	{
		return rect_t(left() + 5, right(), bottom() + 5, top());
	}

	rect_t normal_face()
	{
		return rect_t(left(), right() - 5, bottom(), top() - 5);
	}

	rect_t active_face()
	{
		return rect_t(left() + 3, right() - 2, bottom() + 3, top() - 2);
	}
};
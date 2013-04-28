#include "stdafx.h"
#include "rect_button.h"

void rect_button::render(HDC hdc, PAINTSTRUCT const &ps)
{
	RECT rect(*this);

	rect.left += 5;
	rect.bottom += 5;
	FillRect(hdc, &rect, m_shadow_brush);

	rect.left -= 5;
	rect.bottom -= 5;
	rect.right -= 5;
	rect.top -= 5;
	HBRUSH brush = is_hot() ? m_hot_brush : m_nor_brush;
	FillRect(hdc, &rect, brush);
}

bool rect_button::is_hot() const
{
	auto c = cursor();
	return contains(c.position);
}
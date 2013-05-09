#include "stdafx.h"
#include "RenderAdaptor.h"

void RenderAdaptor::DrawRectangle(int left, int right, int bottom, int top, Color const & c)
{
	RECT rect = {};
	rect.left = left;
	rect.right = right;
	rect.bottom = bottom;
	rect.top = top;

	HBRUSH hbr = CreateSolidBrush(RGB(c.R, c.G, c.B));

	FillRect(mHdc, &rect, hbr);

	DeleteBrush(hbr);
}
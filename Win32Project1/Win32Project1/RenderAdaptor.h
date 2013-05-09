#pragma once
#include "Color.h"

class RenderAdaptor
{
	HDC mHdc;
public:

	explicit RenderAdaptor(HDC h) : mHdc(h) {}

	void DrawRectangle(int left, int right, int bottom, int top, Color const & c);
};
#include "stdafx.h"
#include "Rectangle.h"
#include "RenderAdaptor.h"

void Rectangle::Draw(RenderAdaptor &renderer, Color const &c) const
{
	renderer.DrawRectangle(Left(), Right(), Bottom(), Right(), c);
}
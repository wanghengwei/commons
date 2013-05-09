#pragma once
#include "point.h"
#include "Widget.h"
#include "shape.h"

class MousePointer : public Widget, public Shape
{

	bool m_left_down;

	bool m_right_down;

public:

	MousePointer(Widget *parent) : Widget("__MousePointer", parent), m_left_down(false), m_right_down(false) {}

	void left_down(bool b) { m_left_down = b; }

	bool is_left_down() const { return m_left_down; }

	bool Contains(Point const&) const override { return false; }

	void Draw(RenderAdaptor &, Color const &) const override {}
};
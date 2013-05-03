#pragma once
#include "point.h"
#include "shape.h"

class rect_t : public shape
{
	point_t lb_conor;
	point_t rt_conor;
public:

	rect_t() {}

	~rect_t() {}
	
	rect_t(point_t const &bl, point_t const &tr) : lb_conor(bl), rt_conor(tr) {}
	
	rect_t(int l, int r, int b, int t) : lb_conor(l, b), rt_conor(r, t) {}

	int height() const { return rt_conor.y - lb_conor.y; }
	
	void height(int h) { rt_conor.y = lb_conor.y + h; }
	
	int width() const { return rt_conor.x - lb_conor.x; }
	
	void width(int w) { rt_conor.x = lb_conor.x + w; }

	int left() const { return lb_conor.x; }
	
	int right() const { return rt_conor.x; }
	
	int bottom() const { return lb_conor.y; }
	
	int top() const { return rt_conor.y; }

	void position(point_t const& p) override
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

	bool contains(point_t const &p) const override
	{
		return p.x > lb_conor.x && p.x < rt_conor.x && p.y > lb_conor.y && p.y < rt_conor.y;
	}

	//TODO 这个运算符是平台相关的，并不是矩形的特点，考虑移走
	operator RECT () const
	{
		RECT r;
		r.bottom = lb_conor.y;
		r.left = lb_conor.x;
		r.top = rt_conor.y;
		r.right = rt_conor.x;
		return r;
	}
};
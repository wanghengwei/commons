#pragma once
#include "point.h"

struct rect_t
{
	point_t lb_conor;
	point_t rt_conor;
	rect_t() {}
	rect_t(point_t const &bl, point_t const &tr) : lb_conor(bl), rt_conor(tr) {}
	rect_t(int l, int r, int b, int t) : lb_conor(l, b), rt_conor(r, t) {}

	int height() const { return rt_conor.y - lb_conor.y; }
	void height(int h) { rt_conor.y = lb_conor.y + h; }
	int width() const { return rt_conor.x - lb_conor.x; }
	void width(int w) { rt_conor.x = lb_conor.x + w; }

	bool contains(point_t const &p) const
	{
		return p.x > lb_conor.x && p.x < rt_conor.x && p.y > lb_conor.y && p.y < rt_conor.y;
	}

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
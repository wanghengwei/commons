#pragma once

struct point_t
{
	int x;
	int y;

	point_t(int x, int y) : x(x), y(y) {}

	point_t() : x(0), y(0) {}
};
#pragma once

struct Point
{
	int x;
	int y;

	Point(int x, int y) : x(x), y(y) {}

	Point() : x(0), y(0) {}
};
#pragma once

struct Color
{
	int R;
	int G;
	int B;

	Color(int r, int g, int b) : R(r), G(g), B(b) {}

	Color() : R(0), G(0), B(0) {}

	static Color const Red;
	static Color const Green;
	static Color const Blue;
};


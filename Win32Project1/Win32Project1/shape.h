#pragma once
#include "Point.h"

class RenderAdaptor;
struct Color;

class Shape
{

	Point mPosition;

public:
	
	Shape();

	explicit Shape(Point const &pos) : mPosition(pos) {}

	Shape(int x, int y) : mPosition(Point(x, y)) {}

	virtual ~Shape();

	Point const & Position() const { return mPosition; }

	virtual void Position(Point const &pos)
	{
		mPosition = pos;
	}

	void Position(int x, int y) { Position(Point(x, y)); }

#pragma region 必须实现的方法

	virtual bool Contains(Point const &) const = 0;

	virtual void Draw(RenderAdaptor &, Color const &) const = 0;

#pragma endregion

};


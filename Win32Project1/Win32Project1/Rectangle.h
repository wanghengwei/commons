#pragma once
#include "Shape.h"
#include "Color.h"

class Rectangle : public Shape
{

	Point mOppositeCorner;

public:

	Rectangle() {}

	Rectangle(Point const &pos, Point const &corner) : Shape(pos), mOppositeCorner(corner) {}
	
	Rectangle(int l, int r, int b, int t) : Shape(l, b), mOppositeCorner(r, t) {}

	~Rectangle() {}

#pragma region Base Properties

	int Height() const { return mOppositeCorner.y - Position().y; }
	
	void Height(int h) { mOppositeCorner.y = Position().y + h; }
	
	int Width() const { return mOppositeCorner.x - Position().x; }
	
	void Width(int w) { mOppositeCorner.x = Position().x + w; }

	int Left() const { return Position().x; }
	
	int Right() const { return mOppositeCorner.x; }
	
	int Bottom() const { return Position().y; }
	
	int Top() const { return mOppositeCorner.y; }

#pragma endregion

#pragma region Override Shape

	void Position(Point const& p) override
	{
		int h = Height();
		int w = Width();

		Shape::Position(p);

		Height(h);
		Width(w);
	}

	using Shape::Position;

	bool Contains(Point const &p) const override
	{
		return p.x > Position().x && p.x < mOppositeCorner.x && p.y > Position().y && p.y < mOppositeCorner.y;
	}

	void Draw(RenderAdaptor &renderer, Color const &) const override;

#pragma endregion

	//TODO 这个运算符是平台相关的，并不是矩形的特点，考虑移走
	//operator RECT () const
	//{
	//	RECT r;
	//	r.bottom = lb_conor.y;
	//	r.left = lb_conor.x;
	//	r.top = rt_conor.y;
	//	r.right = rt_conor.x;
	//	return r;
	//}
};
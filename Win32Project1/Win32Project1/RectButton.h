#pragma once
#include "button.h"
#include "Rectangle.h"
#include "state.h"

class RectButton : public button, public Rectangle, public StateMachine
{
public:
	RectButton(std::string const &id, Widget *parent) : 
		button(id, parent), 
		Rectangle(0, 60, 0, 30)
	{
	
	}

	Output Transit(PaintEvent const &e) override;

private:
	Rectangle shadow_face()
	{
		return Rectangle(Left() + 5, Right(), Bottom() + 5, Top());
	}

	Rectangle normal_face()
	{
		return Rectangle(Left(), Right() - 5, Bottom(), Top() - 5);
	}

	Rectangle active_face()
	{
		return Rectangle(Left() + 3, Right() - 2, Bottom() + 3, Top() - 2);
	}
};
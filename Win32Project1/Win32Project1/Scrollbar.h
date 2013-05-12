#pragma once
#include "widget.h"
#include "Rectangle.h"
#include "state.h"
#include <string>

class Scrollbar : public Widget, public Rectangle, public OldStateMachine
{
	Rectangle mSlider;
	Rectangle mBack;

public:

	Scrollbar(std::string const &id, Widget *p) : Widget(id, p), mBack(0, 20, 0, 200), mSlider(0, 20, 0, 15) {}

	Output Transit(PaintEvent const &e) override
	{
		return [&e, this]()
		{
			this->mBack.Draw(e.Renderer(), Color::Red);
			this->mSlider.Draw(e.Renderer(), Color::Green);
		};
	}

};
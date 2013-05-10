#pragma once
#include "Events.h"
#include <functional>

class Widget;

struct state
{
	Widget *hot_widget;

	Widget *active_widget;

	int background_index;

	HBRUSH pre_defined_background[2];

	state() : hot_widget(nullptr), active_widget(nullptr), background_index(0)
	{
		pre_defined_background[0] = CreateSolidBrush(RGB(0, 255, 255));
		pre_defined_background[1] = CreateSolidBrush(RGB(255, 0, 0));
	}
};

typedef std::function<void ()> Output;

class StateMachine
{
public:
	virtual Output Transit(PaintEvent const &)
	{
		return Output();
	}

	virtual Output Transit(ReSizedEvent const &)
	{
		return Output();
	}

};
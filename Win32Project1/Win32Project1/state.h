#pragma once

class widget;

struct state
{
	widget *hot_widget;

	widget *active_widget;

	int background_index;

	HBRUSH pre_defined_background[2];

	state() : hot_widget(nullptr), active_widget(nullptr), background_index(0)
	{
		pre_defined_background[0] = CreateSolidBrush(RGB(0, 255, 255));
		pre_defined_background[1] = CreateSolidBrush(RGB(255, 0, 0));
	}
};